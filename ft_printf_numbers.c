/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 01:02:46 by lprates           #+#    #+#             */
/*   Updated: 2021/04/01 03:40:14 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static char	*ft_int_or_uint(long i, t_settings *sets)
{
	if (i < 0)
	{
		sets->negative = true;
		return (ft_itoa(i));
	}
	return (ft_uitoa(i));
}

char	*ft_spaces_or_zeros(char *nstr, int *len, t_settings *sets)
{
	if (*len > 0 && sets->zero && (sets->precision < 0 || !sets->dot))
		return (ft_add_zeros(nstr, len, sets));
	else if (*len > 0)
		return (ft_add_spaces(nstr, *len));
	return (nstr);
}

int	ft_write_int(long i, t_settings *sets)
{
	char	*nstr;
	int		len;

	nstr = ft_int_or_uint(i, sets);
	len = ft_strlen(nstr);
	if (sets->dot)
		nstr = ft_int_precision(nstr, sets, &len, i);
	if (sets->plus && i >= 0 && !sets->zero)
		nstr = freejoin("+", nstr);
	if (sets->space && i >= 0)
		nstr = freejoin(" ", nstr);
	len = sets->width - ft_strlen(nstr);
	if (!sets->minus)
		nstr = ft_spaces_or_zeros(nstr, &len, sets);
	if (sets->minus && len > 0 && sets->width > sets->precision)
		nstr = ft_add_spaces_after(nstr, len);
	ft_putstr(nstr);
	len = ft_strlen(nstr);
	free(nstr);
	return (len);
}

int	ft_write_hexa(unsigned int i, t_settings *sets, char fmt)
{
	char	*nstr;
	int		len;

	nstr = ft_uint_to_hexa(i);
	len = ft_strlen(nstr);
	if (sets->dot)
		nstr = ft_int_precision(nstr, sets, &len, i);
	if (sets->pound && i != 0)
		nstr = freejoin("0x", nstr);
	if (fmt == 'X')
		nstr = ft_strupcase(nstr);
	len = sets->width - ft_strlen(nstr);
	if (!sets->minus)
		nstr = ft_spaces_or_zeros(nstr, &len, sets);
	len = sets->width - ft_strlen(nstr);
	if (sets->minus && len > 0 && sets->width > sets->precision)
		nstr = ft_add_spaces_after(nstr, len);
	ft_putstr(nstr);
	len = ft_strlen(nstr);
	free(nstr);
	return (len);
}

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
		if (sets->zero && (sets->precision < 0 || !sets->dot))
			nstr = ft_add_zeros(nstr, &len, sets);
		else if (len > 0)
			nstr = ft_add_spaces(nstr, len);
	}
	len = sets->width - ft_strlen(nstr);
	if (sets->minus && len > 0 && sets->width > sets->precision)
		nstr = ft_add_spaces_after(nstr, len);
	ft_putstr(nstr);
	len = ft_strlen(nstr);
	free(nstr);
	return (len);
}
