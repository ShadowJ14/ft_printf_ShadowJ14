/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:43:19 by lprates           #+#    #+#             */
/*   Updated: 2021/03/24 22:11:13 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

static int		c_int(unsigned int n)
{
	int count;

	if (n == 0)
		return (1);
	count = 1;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char		*loc_swap(char *ret, size_t i)
{
	char	tmp;
	size_t	t;
	size_t	n;

	t = 0;
	n = i;
	while (t < ((n + 1) / 2))
	{
		tmp = ret[t];
		ret[t++] = ret[i];
		ret[i--] = tmp;
	}
	ret[n + 1] = 0;
	return (ret);
}

char			*ft_uitoa(unsigned int n)
{
	char	*ret;
	size_t	i;
	long	t;

	i = 0;
	t = n;
	ret = malloc(c_int(t) + 1);
	if (!ret)
		return (NULL);
	if (t == 0)
	{
		ret[i] = '0';
		return (loc_swap(ret, i));
	}
	ret[i++] = 0;
	while (t != 0)
	{
		ret[i++] = (t % 10) + '0';
		t /= 10;
	}
	return (loc_swap(ret, i - 1));
}
