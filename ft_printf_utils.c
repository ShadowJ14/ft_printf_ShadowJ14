/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 01:47:47 by lprates           #+#    #+#             */
/*   Updated: 2021/04/01 03:31:19 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include "./libft/libft.h"

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

char	*ft_add_spaces(char *s, int len)
{
	char	*tmp;

	tmp = loc_calloc(1, len, ' ');
	s = freejoin(tmp, s);
	free(tmp);
	return (s);
}

char	*ft_add_spaces_after(char *s, int len)
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
	char	*s2;

	s2 = s;
	if (sets->plus && !sets->negative)
	{
		tmp = (char *)loc_calloc(1, *len, '0');
		tmp = freejoin("+", tmp);
		s = ft_strjoin(tmp, s + 1);
		free(s2);
	}
	else if (sets->negative)
	{
		tmp = (char *)loc_calloc(1, *len, '0');
		tmp = freejoin("-", tmp);
		s = ft_strjoin(tmp, s + 1);
		free(s2);
	}
	else
	{
		tmp = loc_calloc(1, *len, '0');
		s = freejoin(tmp, s);
	}
	free(tmp);
	return (s);
}
