/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 01:55:56 by lprates           #+#    #+#             */
/*   Updated: 2021/04/01 02:08:29 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_write_char(char c, t_settings *sets)
{
	int	w;

	w = sets->width - 1;
	if (!sets->minus)
	{
		if (sets->zero)
			ft_putzeros(w);
		else
			ft_putblanks(w);
	}
	ft_putchar(c);
	if (sets->minus)
		ft_putblanks(w);
	w = ft_isbigger(sets->width, 1);
	return (w);
}

//makes this better with addzeros
int	ft_writeconv_string(char *s, t_settings *sets)
{
	int		w;
	char	*sub;

	if (sets->dot)
	{
		if (sets->precision)
			sub = ft_substr(s, 0, sets->precision);
		else
			sub = ft_strdup("");
	}
	else
		sub = ft_strdup(s);
	if (!sets->minus)
	{
		if (sets->zero)
			ft_putzeros(sets->width - ft_strlen(sub));
		else
			ft_putblanks(sets->width - ft_strlen(sub));
	}
	ft_putstr(sub);
	if (sets->minus)
		ft_putblanks(sets->width - ft_strlen(sub));
	w = ft_isbigger(sets->width, ft_strlen(sub));
	free(sub);
	return (w);
}
