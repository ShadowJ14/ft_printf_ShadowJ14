/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 12:48:17 by lprates           #+#    #+#             */
/*   Updated: 2021/04/01 02:56:59 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void	ft_init_struct(t_settings *sets)
{
	sets->minus = false;
	sets->dot = false;
	sets->zero = false;
	sets->asterisk = false;
	sets->dotastrsk = false;
	sets->width = 0;
	sets->precision = 0;
	sets->ccount = 0;
	sets->negative = false;
	sets->pound = false;
	sets->plus = false;
	sets->space = false;
}

int	ft_convert(char fmt, va_list *ap, t_settings *sets)
{
	unsigned long	p;
	int				count;

	count = 0;
	if (ft_strchr(CONVAINTS, fmt))
		count = ft_handle_ints(fmt, ap, sets);
	else if (fmt == 's')
		count = ft_handle_strings(ap, sets);
	else if (fmt == 'p')
	{
		p = va_arg(*ap, unsigned long);
		count = ft_write_pointer(p, sets);
	}
	if (count)
		return (count);
	return (0);
}

void	ft_setflags(char *format, t_settings *sets, va_list *ap)
{
	if (*format == '#')
		sets->pound = true;
	else if (*format == '+')
		sets->plus = true;
	else if (*format == ' ' && !sets->plus)
		sets->space = true;
	else if (*format == '-')
		sets->minus = true;
	else if (*format == '0' && !sets->minus && !sets->dot)
		sets->zero = true;
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
		ft_handle_dotflag(format, ap, sets);
}

int	ft_isvalid(char *format, t_settings *sets, va_list *ap)
{
	char	*tmp;
	char	*ret;

	tmp = format;
	while (ft_strchr(FLAGS, *format) && *format)
		ft_setflags(format++, sets, ap);
	if (ft_strchr("0123456789\0", *format) && sets->dot == false)
	{
		sets->width = ft_atoi(format);
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
	return (format - tmp);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_settings	sets;
	static int	count = 0;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			ft_init_struct(&sets);
			format++;
			if (*format == '%')
			{
				format += ft_myputchar(*format, &count);
				continue ;
			}
			format += ft_isvalid((char *)format, &sets, &ap);
			count += ft_convert(*format, &ap, &sets);
			format++;
		}
		else
			format += ft_myputchar(*format, &count);
	}
	va_end(ap);
	return (count);
}
