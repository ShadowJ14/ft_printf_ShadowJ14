/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 01:02:46 by lprates           #+#    #+#             */
/*   Updated: 2021/05/12 22:46:24 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

/*
** handles if value is inside int or uint ranges
** to call appropriate conversion function
** this allows both to be handled by ft_write_number
*/

static char	*ft_int_or_uint(long i, t_settings *sets)
{
	if (i < 0)
	{
		sets->negative = true;
		sets->plus = false;
		return (ft_itoa(i));
	}
	if (i == 0)
		sets->nzero = true;
	return (ft_uitoa(i));
}

/*
** handles usage of spaces or zeros depending on the flags used
** used to handle pound (#) flag for bonus section of exercise
*/

char	*ft_spaces_or_zeros(char *nstr, int *len, t_settings *sets)
{
	if (*len > 0 && sets->zero && (sets->precision < 0 || !sets->dot))
	{
		if (sets->pound && *len - 2 < 0 && !sets->nzero)
			return (nstr);
		return (ft_add_zeros(nstr, len, sets));
	}
	else if (*len > 0)
	{
		if (sets->pound && !sets->nzero)
		{
			sets->pound = false;
			nstr = freejoin("0x", nstr);
			*len = sets->width - ft_strlen(nstr);
		}
		if (*len > 0)
			return (ft_add_spaces_right(nstr, *len));
	}
	return (nstr);
}

/*
** this only handles int and uint values as part of
** the mandatory section of the exercise.
** builds the string according to the flags set
*/

int	ft_write_number(long i, t_settings *sets)
{
	char	*nstr;
	int		len;

	nstr = ft_int_or_uint(i, sets);
	len = ft_strlen(nstr);
	if (sets->dot)
		nstr = ft_int_precision(nstr, sets, &len, i);
	if (sets->plus && i >= 0)
		nstr = freejoin("+", nstr);
	len = sets->width - ft_strlen(nstr);
	if (sets->space && i >= 0 && !sets->plus)
		len = len - 1;
	if (!sets->minus)
		nstr = ft_spaces_or_zeros(nstr, &len, sets);
	if (sets->minus && len > 0 && sets->width > sets->precision)
		nstr = ft_add_spaces_left(nstr, len);
	if (sets->space && i >= 0 && !sets->plus)
		nstr = freejoin(" ", nstr);
	ft_putstr(nstr);
	len = ft_strlen(nstr);
	free(nstr);
	return (len);
}

/*
** this handles hexadecimal numbers, building the string
** according to the flags set
*/

int	ft_write_hexa(unsigned int i, t_settings *sets, char fmt)
{
	char	*nstr;
	int		len;

	if (i == 0)
		sets->nzero = true;
	nstr = ft_uint_to_hexa(i);
	len = ft_strlen(nstr);
	if (sets->dot)
		nstr = ft_int_precision(nstr, sets, &len, i);
	len = sets->width - ft_strlen(nstr);
	if (!sets->minus)
		nstr = ft_spaces_or_zeros(nstr, &len, sets);
	if (sets->pound && i != 0)
		nstr = freejoin("0x", nstr);
	if (fmt == 'X')
		nstr = ft_strupcase(nstr);
	len = sets->width - ft_strlen(nstr);
	if (sets->minus && len > 0 && sets->width > sets->precision)
		nstr = ft_add_spaces_left(nstr, len);
	ft_putstr(nstr);
	len = ft_strlen(nstr);
	free(nstr);
	return (len);
}

/*
** this handles address values, here interpreted as an hexadecimal number,
** building the string according to the flags set
*/

int	ft_write_pointer(unsigned long i, t_settings *sets)
{
	char	*nstr;
	int		len;

	nstr = ft_uint_to_hexa(i);
	nstr = freejoin("0x", nstr);
	len = ft_strlen(nstr);
	if (sets->dot)
		nstr = ft_int_precision(nstr, sets, &len, (long)i);
	len = sets->width - len;
	if (!sets->minus)
	{
		if (sets->zero && len > 0 && (sets->precision < 0 || !sets->dot))
			nstr = ft_add_zeros(nstr, &len, sets);
		else if (len > 0)
			nstr = ft_add_spaces_right(nstr, len);
	}
	len = sets->width - ft_strlen(nstr);
	if (sets->minus && len > 0 && sets->width > sets->precision)
		nstr = ft_add_spaces_left(nstr, len);
	ft_putstr(nstr);
	len = ft_strlen(nstr);
	free(nstr);
	return (len);
}
