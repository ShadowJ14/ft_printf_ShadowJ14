/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 23:55:21 by lprates           #+#    #+#             */
/*   Updated: 2021/02/17 17:31:06 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		j;
	int		k;
	int		v;
	size_t	t;

	i = 0;
	j = 0;
	v = 1;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] != '\0' && len-- > 0)
		if (big[i++] == little[j])
		{
			k = i - 1;
			t = len + 2;
			while (little[j] != 0 && --t > 0)
				if (little[j++] != big[k++])
					v = 0;
			if (v == 1 && little[j] == 0)
				return ((char *)&big[i - 1]);
			j = 0;
			v = 1;
		}
	return (NULL);
}
