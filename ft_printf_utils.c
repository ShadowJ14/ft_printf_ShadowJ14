/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 01:47:47 by lprates           #+#    #+#             */
/*   Updated: 2021/05/12 22:46:30 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include "./libft/libft.h"

/*
** handles when printing the percentage convertion char
*/

int	ft_print_pct(t_settings *sets)
{
	int		len;
	char	*sub;

	sub = ft_strdup("%");
	len = sets->width - ft_strlen(sub);
	if (!sets->minus)
		sub = ft_spaces_or_zeros(sub, &len, sets);
	if (sets->minus)
		sub = ft_add_spaces_left(sub, len);
	ft_putstr(sub);
	len = ft_strlen(sub);
	free(sub);
	return (len);
}

/*
** handles the precision values
*/

char	*ft_int_precision(char *s, t_settings *sets, int *len, int i)
{
	char	*tmp;
	char	*s2;

	s2 = s;
	if (sets->precision >= *len)
	{
		*len = sets->precision - *len;
		if (sets->negative)
		{
			tmp = (char *)loc_calloc(1, *len + 1, '0');
			tmp = freejoin("-", tmp);
			s = ft_strjoin(tmp, s + 1);
			free(s2);
		}
		else
		{
			tmp = (char *)loc_calloc(1, *len, '0');
			s = freejoin(tmp, s);
		}
		free(tmp);
	}
	else if (i == 0)
		s = free_substr(s, sets->precision);
	*len = ft_strlen(s);
	return (s);
}

/*
** adds spaces to the end of s string
*/

char	*ft_add_spaces_right(char *s, int len)
{
	char	*tmp;

	tmp = loc_calloc(1, len, ' ');
	s = freejoin(tmp, s);
	free(tmp);
	return (s);
}

/*
** adds spaces to the beginning of s string
*/

char	*ft_add_spaces_left(char *s, int len)
{
	char	*tmp;
	char	*s2;

	tmp = loc_calloc(1, len, ' ');
	s2 = freejoin(s, tmp);
	free(s);
	return (s2);
}

char	*ft_add_zeros(char *s, int *len, t_settings *sets)
{
	char	*tmp;

	tmp = NULL;
	if (sets->plus || sets->negative)
		s = handle_plus_negative(len, s, tmp, sets);
	else
	{
		if (sets->pound && !sets->nzero)
			*len -= 2;
		if (sets->space && !sets->zero)
			*len -= 1;
		tmp = loc_calloc(1, *len, '0');
		s = freejoin(tmp, s);
		if (sets->pound && !sets->nzero)
		{
			sets->pound = false;
			s = freejoin("0x", s);
		}
	}
	free(tmp);
	return (s);
}
