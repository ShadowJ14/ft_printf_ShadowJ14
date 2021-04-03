/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 02:13:01 by lprates           #+#    #+#             */
/*   Updated: 2021/04/03 11:37:39 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	*loc_calloc(size_t count, size_t size, char c)
{
	char	*tmp;

	if (size == 1)
		tmp = (char *)malloc((count * size) + 1);
	else
		tmp = (char *)malloc((count * size) + 1);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, c, count * size);
	tmp[size] = 0;
	return (tmp);
}

char	*freejoin(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s2);
	return (tmp);
}

char	*free_substr(char *s1, int p)
{
	char	*tmp;
	int		c;

	c = 0;
	tmp = ft_substr(s1, 0, p);
	free(s1);
	return (tmp);
}
