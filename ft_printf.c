/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 12:48:17 by lprates           #+#    #+#             */
/*   Updated: 2021/03/27 17:24:25 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		ft_writeconv_int(int c, char fmt, t_settings *sets)
{
	int count;

	count = 0;
	// done seems to be working
	if (fmt == 'c')
		count = ft_write_char(c, sets);
	// done, seems to be working
	else if (fmt == 'd' || fmt == 'i')
		count = ft_write_int(c, sets);
	else if (fmt == 'x' || fmt == 'X')
		count = ft_write_hexa(c, sets, fmt);
	else
		count = ft_write_uint(c, sets);
	return (count);
}

/*
** s done seems to be working
**
*/

int	ft_convert(char fmt, va_list *ap, t_settings *sets)
{
	char	*s;
	long	c;
	unsigned int	p;
	int		count;

	count = 0;
	if (ft_strchr(CONVAINTS, fmt))
	{
		if (ft_strchr(CONVUINTS, fmt))
			c = va_arg(*ap, unsigned int);
		else
			c = va_arg(*ap, int);
		count = ft_writeconv_int(c, fmt, sets);
	}
	else if (fmt == 's')
	{
		if (!(s = va_arg(*ap, char *)))
			count = ft_writeconv_string("(null)", sets);
		else
			count = ft_writeconv_string(s, sets);
	}
	else if (fmt == 'p')
	{
		p = va_arg(*ap, unsigned int);
		count = ft_write_pointer(p, sets);
	}
	if (count)
		return (count);
	return (0);
}

void		ft_setflags(char *format, t_settings *sets, va_list *ap)
{
	if (*format == '0' && !sets->minus && !sets->dot)
		sets->zero = true;
	else if (*format == '-')
	{
		sets->minus = true;
		sets->zero = false;
	}
	else if (*format == '*' && sets->dot == false)
	{
		sets->width = va_arg(*ap, int);
		if (sets->width < 0)
		{
			sets->minus = true;
			sets->zero = false;
			sets->width *= -1;
		}
	}
	else if (*format == '.')
	{
		sets->dot = true;
		if (*(format + 1) == '*')
			sets->precision = va_arg(*ap, int);
		else
			sets->precision = ft_atoi(format + 1);
	}
}

/*
** seems to be working for defined flags
** may add plus after for bonus
*/

int		ft_isvalid(char *format, t_settings *sets, va_list *ap)
{
	char *tmp;
	char *ret;

	tmp = format;
	while (ft_strchr(FLAGS, *format) && *format)
	{
		ft_setflags(format, sets, ap);
		format++;
	}
	if (ft_strchr("0123456789\0", *format) && sets->dot == false)
	{
		sets->width = ft_atoi(format);
		// a fix
		ret = ft_itoa(sets->width);
		format += ft_strlen(ret);
		free(ret);
	}
	if (*format == '.')
		ft_setflags(format++, sets, ap);
	if (*format == '*')
		format++;
	while (ft_strchr("0123456789\0", *format))
	{
		ret = ft_itoa(sets->precision);
		format += ft_strlen(ret);
		free(ret);
	}
	if (ft_strchr(CONV, *format) != 0)
		return (format - tmp);
	else
		return (0);
}

// needed to start va_list
// need to check this:
// https://stackoverflow.com/questions/14768230/malloc-for-struct-and-pointer-in-c
/*
void	ft_free_sets(t_settings *sets)
{
	free(sets->width);
}*/

int		ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	t_settings	sets;
	int			count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			ft_init_struct(&sets);
			format++;
			if (*format == '%')
			{
				write(1, format++, 1);
				count++;
				continue;
			}
			sets.ccount = ft_isvalid((char *)format, &sets, &ap);
			format += sets.ccount;
			count += ft_convert(*format, &ap, &sets);
			//ft_free_sets(&sets);
			format++;
		}
		else
		{
			write(1, format++, 1);
			count++;
		}
	}
	va_end(ap);
	return (count);
}

/*
int main()
{
	char *str = "Ola";
	unsigned int daf = 2147489999;
	int xyz = -2147483647;
	int abc = 4;
	char t = 'a';
	float f = 5.45;
	//printf("ft_printf count: %i\n", ft_printf("start mine:    as%10cdc%-*shaj%%b\n", t, 50, str));
	//printf("printf count: %i\n", printf("start printf:  asdchaj%*pb\n", 20, str));
	//printf("loc itoa: %s\n", loc_itoa(daf));
	printf("\nftprint count: %i\n", ft_printf(" 0*%0-*i*0 0*%0*i*0 ", 21, 1021, 21, -1011));
	printf("\nprint count: %i\n", printf(" 0*%0-*i*0 0*%0*i*0 ", 21, 1021, 21, -1011));
	//printf("start printf: a%10cjsd%0.*ich%fa%sj\n", t, 1, daf, f, str);
	//printf("")
	//int x = ft_isvalid("10cha%sj\n");
	//printf("%i\n", x);
}*/
