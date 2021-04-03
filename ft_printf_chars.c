/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 01:55:56 by lprates           #+#    #+#             */
/*   Updated: 2021/04/03 11:37:13 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_isbigger(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	ft_putblanks(int len)
{
	while (len > 0)
	{
		ft_putchar(' ');
		len--;
	}
	return ;
}

void	ft_putzeros(int len)
{
	while (len > 0)
	{
		ft_putchar('0');
		len--;
	}
	return ;
}

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

int	ft_writeconv_string(char *s, t_settings *sets)
{
	int		len;
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
	len = sets->width - ft_strlen(sub);
	if (!sets->minus)
		sub = ft_spaces_or_zeros(sub, &len, sets);
	if (sets->minus)
		sub = ft_add_spaces_after(sub, len);
	ft_putstr(sub);
	len = ft_strlen(sub);
	free(sub);
	return (len);
}
