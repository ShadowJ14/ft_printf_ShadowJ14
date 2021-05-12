/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 00:45:06 by lprates           #+#    #+#             */
/*   Updated: 2021/05/12 22:46:22 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

/*
** handles the conversion specifiers that use ints and uints
** to get the correct type from va_arg()
*/

int	ft_handle_ints(char fmt, va_list *ap, t_settings *sets)
{
	long	c;
	int		count;

	count = 0;
	if (ft_strchr(CONVUINTS, fmt))
		c = va_arg(*ap, unsigned int);
	else
		c = va_arg(*ap, int);
	count = ft_writeconv_int(c, fmt, sets);
	return (count);
}

/*
** handles the string conversion specifier
** and the situation where va_arg() retrives a NULL
*/

int	ft_handle_strings(va_list *ap, t_settings *sets)
{
	char	*s;
	int		count;

	count = 0;
	s = va_arg(*ap, char *);
	if (!s)
		count = ft_write_string("(null)", sets);
	else
		count = ft_write_string(s, sets);
	return (count);
}

void	ft_handle_dotflag(char *format, va_list *ap, t_settings *sets)
{
	sets->dot = true;
	if (*(format + 1) == '*')
		sets->precision = va_arg(*ap, int);
	else
		sets->precision = ft_atoi(format + 1);
	return ;
}

/*
** handles the value retrieved from va_args()
** that corresponds to all int type conversion specifiers
*/

int	ft_writeconv_int(long c, char fmt, t_settings *sets)
{
	int	count;

	if (fmt == 'c')
		return (count = ft_write_char(c, sets));
	if (fmt == 'd' || fmt == 'i' || fmt == 'u')
		return (count = ft_write_number(c, sets));
	return (count = ft_write_hexa(c, sets, fmt));
}

/*
** modified version of putchar that increments
** the value being pointed by count and
** returns 1 to increment the address value of format
** in ft_printf
*/

int	ft_myputchar(char format, int *count)
{
	write(1, &format, 1);
	*count = *count + 1;
	return (1);
}
