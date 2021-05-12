/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 02:13:01 by lprates           #+#    #+#             */
/*   Updated: 2021/05/10 20:03:34 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

/*
** slight variation of ft_calloc from libft
** to place a value defined in the input when doing calloc
** instead of filling the memory with 0's
*/

void	*loc_calloc(size_t count, size_t size, char c)
{
	char	*tmp;

	if (size == 1)
		tmp = (char *)malloc((count * size) + 2);
	else
		tmp = (char *)malloc((count * size) + 1);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, c, count * size);
	tmp[size] = 0;
	return (tmp);
}

/*
** freejoin is used to free s2, so tmp can be returned to
** the variable used as input when the function is called
** ex: s2 = freejoin(s1, s2)
*/

char	*freejoin(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s2);
	return (tmp);
}

/*
** same logic as freejoin but for ft_substr
*/

char	*free_substr(char *s1, int p)
{
	char	*tmp;

	tmp = ft_substr(s1, 0, p);
	free(s1);
	return (tmp);
}

char	*handle_plus_negative(int *len, char *s, char *tmp, t_settings *sets)
{
	char	*s2;

	s2 = s;
	tmp = (char *)loc_calloc(1, *len, '0');
	if (sets->plus)
		tmp = freejoin("+", tmp);
	else
		tmp = freejoin("-", tmp);
	s = ft_strjoin(tmp, s + 1);
	free(tmp);
	free(s2);
	return (s);
}
