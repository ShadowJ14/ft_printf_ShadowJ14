/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:48:01 by lprates           #+#    #+#             */
/*   Updated: 2021/02/15 20:32:08 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*loc_malloc(char *s, size_t start, size_t len)
{
	char	*sub;

	if ((size_t)ft_strlen(s) < start)
	{
		if (!(sub = malloc(sizeof(char) * 1)))
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	else if (len > (size_t)ft_strlen(s))
	{
		if (!(sub = malloc(sizeof(char) * (size_t)ft_strlen(s) + 1)))
			return (NULL);
	}
	else
	{
		if (!(sub = malloc(sizeof(char) * len + 1)))
			return (NULL);
	}
	return (sub);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (!(sub = loc_malloc((char *)s, start, len)))
		return (NULL);
	if (len > ft_strlen(s) && start == 0)
	{
		ft_strlcpy(sub, (char*)s, len);
		return (sub);
	}
	while ((size_t)i < len && start < ft_strlen(s) + 1)
	{
		if ((sub[i++] = s[start++]) == '\0')
			return (sub);
	}
	sub[i] = 0;
	return (sub);
}
