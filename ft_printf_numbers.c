/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 01:02:46 by lprates           #+#    #+#             */
/*   Updated: 2021/04/01 01:45:26 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_write_int(long i, t_settings *sets)
{
	char	*nstr;
	int		len;

	if (i < 0)
	{
		sets->negative = true;
		nstr = ft_itoa(i);
	}
	else
		nstr = ft_uitoa(i);
	len = ft_strlen(nstr);
	if (sets->dot)
		nstr = ft_int_precision(nstr, sets, &len, i);
	if (sets->plus && i >= 0 && !sets->zero)
		nstr = freejoin("+", nstr);
	if (sets->space && i >= 0)
		nstr = freejoin(" ", nstr);
	len = sets->width - ft_strlen(nstr);
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
