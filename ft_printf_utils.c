/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 01:47:47 by lprates           #+#    #+#             */
/*   Updated: 2021/03/24 22:53:33 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include "./libft/libft.h"

int		ft_isbigger(int a, int b)
{
	return ((a >= b) ? a : b);
}

// care for name
static void	*loc_calloc(size_t count, size_t size)
{
	char	*tmp;

	if (size == 1)
		tmp = (char *)malloc((count * size) + 1);
	else
		tmp = (char *)malloc((count * size) + 1);
	if (!tmp)
		return (NULL);
	// this is changed from original calloc
	ft_memset(tmp, '0', count * size);
	tmp[size] = 0;
	return (tmp);
}

char	*freejoin(char *(*f)(STRJOINARGS), char *s1, char *s2)
{
	char *tmp;

	tmp = f(s2, s1);
	free(s1);
	return (tmp);
}

char	*fsbstr(char *(*f)(SUBSTRARGS), char *s1, int p)
{
	char	*tmp;
	int		c;

	c = 0;
	tmp = f(s1, 0, p);
	free(s1);
	return (tmp);
}

// seems to be working
int		ft_write_int(int i, t_settings *sets)
{
	char *nstr;
	char *tmp;
	int len;
	int t;

	t = i;
	if (i < 0)
		i *= -1;
	nstr = ft_itoa(i);
	len = ft_strlen(nstr);
	if (sets->dot)
	{
		if (sets->precision > len)
		{
			len = sets->precision - len;
			tmp = (char *)loc_calloc(1, len);
			if (t < 0)
				tmp = freejoin(ft_strjoin, tmp, "-");
			nstr = freejoin(ft_strjoin, nstr, tmp);
			len = ft_strlen(nstr);
			free(tmp);
		}
		else if (i == 0)
			nstr = fsbstr(ft_substr, nstr, sets->precision);
	}
		//printf("len before: %i\n", len);
	len = sets->width - len;
	//printf("len: %i\n width: %i\n", len, sets->width);
	if (!sets->minus)
	{
		if(t < 0 && !sets->dot)
		{
			ft_putchar('-');
			len -= 1;
		}
		if (sets->zero && t > 0)
			ft_putzeros(len);
		else
			ft_putblanks(len);
	}
	ft_putstr(nstr);
	if (sets->minus)
		ft_putblanks(len);
	len = ft_strlen(nstr);
	free(nstr);
	if (t < 0)
		return (ft_isbigger(sets->width, len + 1));
	return (ft_isbigger(sets->width, len));
}

int		ft_write_uint(unsigned int i, t_settings *sets)
{
	char *nstr;
	char *tmp;
	int len;

	nstr = ft_uitoa(i);
	len = ft_strlen(nstr);
	if (sets->dot && sets->precision > len)
	{
		len = sets->precision - len;
		tmp = (char *)loc_calloc(1, len);
		nstr = ft_strjoin(tmp, nstr);
		len = ft_strlen(nstr);
		free(tmp);
	}
	len = sets->width - len;
	if (!sets->minus)
		ft_putblanks(len);
	ft_putstr(nstr);
	if (sets->minus)
		ft_putblanks(len);
	len = ft_strlen(nstr);
	free(nstr);
	return (ft_isbigger(sets->width, len));
}
 // these should stay in printf_utils

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

int		ft_write_hexa(unsigned int i, t_settings *sets, char fmt)
{
	char	*nstr;
	char	*tmp;
	int		len;

	nstr = ft_uint_to_hexa(i);
	if (fmt == 'X')
		nstr = ft_strupcase(nstr);
	len = ft_strlen(nstr);
	if (sets->dot && sets->precision > len)
	{
		len = sets->precision - len;
		tmp = (char *)loc_calloc(1, len);
		nstr = ft_strjoin(tmp, nstr);
		len = ft_strlen(nstr);
		free(tmp);
	}
	len = sets->width - len;
	if (!sets->minus)
		ft_putblanks(len);
	ft_putstr(nstr);
	if (sets->minus)
		ft_putblanks(len);
	free(nstr);
	return (ft_isbigger(sets->width, ft_strlen(nstr)));
}

// seems to be working

int		ft_write_char(char c, t_settings *sets)
{
	int		w;

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

// seems to be working

int		ft_writeconv_string(char *s, t_settings *sets)
{
	int		w;
	char	*sub;

	if (sets->dot)
		if (sets->precision)
			sub = ft_substr(s, 0, sets->precision);
		else
			sub = ft_strdup("");
	else
		sub = ft_strdup(s);
	w = sets->width - ft_strlen(sub);
	if (!sets->minus)
	{
		if (sets->zero)
			ft_putzeros(w);
		else
			ft_putblanks(w);
	}
	ft_putstr(sub);
	if (sets->minus)
		ft_putblanks(w);
	w = ft_isbigger(sets->width, ft_strlen(sub));
	free(sub);
	return (w);
}

void	ft_init_struct(t_settings *sets)
{
	sets->minus = false;
	sets->dot = false;
	sets->zero = false;
	sets->asterisk = false;
	sets->dotastrsk = false;
	sets->width = 0;
	sets->precision = 0;
	sets->ccount = 0;
}

int		ft_write_pointer(unsigned int i, t_settings *sets)
{
	char	*nstr;
	char	*tmp;
	int		len;

	nstr = ft_uint_to_hexa(i);
	nstr = ft_strjoin("0x10", nstr);
	len = ft_strlen(nstr);
	if (sets->dot && sets->precision > len)
	{
		len = sets->precision - len;
		tmp = (char *)loc_calloc(1, len);
		nstr = ft_strjoin(tmp, nstr);
		len = ft_strlen(nstr);
		free(tmp);
	}
	len = sets->width - len;
	if (!sets->minus)
		ft_putblanks(len);
	ft_putstr(nstr);
	if (sets->minus)
		ft_putblanks(len);
	free(nstr);
	return (ft_isbigger(sets->width, ft_strlen(nstr)));
}
