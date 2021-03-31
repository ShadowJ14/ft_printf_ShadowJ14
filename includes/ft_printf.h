/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 12:48:55 by lprates           #+#    #+#             */
/*   Updated: 2021/03/27 19:40:03 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "../libft/libft.h"

# define CONV "cspdiuxX%\0"
# define CONVAINTS "cdiuxX\0"
# define CONVUINTS "uxX\0"
# define CONVDOUBLE "feEgG\0"
# define HEXA "0123456789abcdef\0"
# define NUMBS "0123456789\0"
// remove . (dot) maybe
# define FLAGS "+ #-0.*\0"

# define SUBSTRARGS const char *, unsigned int, size_t
# define STRJOINARGS const char *, const char *
typedef int t_bool;
#define true 1
#define false 0

int	ft_printf(const char *, ...);

// may need more settings like hexa
// and more for bonus
typedef struct s_settings{
	t_bool minus;
	t_bool dot;
	t_bool zero;
	// these two may be unnecessary
	t_bool asterisk;
	t_bool dotastrsk;
	int width;
	// in ints this adds zeros and has priority over width
	// adds more zero even if width is lower
	int precision;
	int ccount;
	t_bool negative;
	t_bool pound;
	t_bool plus;
	t_bool space;
} t_settings;

int		ft_writeconv_string(char *s, t_settings *sets);
int		ft_write_char(char c, t_settings *sets);
int		ft_isbigger(int a, int b);
void	ft_init_struct(t_settings *sets);
int		ft_write_int(int i, t_settings *sets);
char	*ft_uitoa(unsigned int n);
int		ft_write_uint(unsigned int i, t_settings *sets);
char	*ft_uint_to_hexa(unsigned long x);
int		ft_write_hexa(unsigned int i, t_settings *sets, char fmt);
void	ft_putzeros(int len);
void	ft_putblanks(int len);
char	*ft_putblanks_two(char *s, int len);
int		ft_write_pointer(unsigned long i, t_settings *sets);

#endif

// %2*i -> 2 doesnt do anything, same as %*i
// %*2i -> * doesnt do anything, same as %2i
// last is the one that's used
// %*6.*2i or %*.*2i -> * and 6 dont do anything same as %.*2i
// asterisk (first) is used for zeros and number(next) for width
// %.*i6 is the same as %.**i -> first sets zeros and second width
// dot sets the usage it seems
// %*.**20i -> 1st * nothing, 2nd * after . zeros, 3rd * nothing, number ate end sets width
// seems the width is set by the last number/asterisk not following a dot
// dot acts the same way, only last .value is used
