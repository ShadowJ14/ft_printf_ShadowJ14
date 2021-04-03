/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 12:48:55 by lprates           #+#    #+#             */
/*   Updated: 2021/04/03 14:23:21 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONV "cspdiuxX%\0"
# define CONVAINTS "cdiuxX\0"
# define CONVUINTS "uxX\0"
# define CONVDOUBLE "feEgG\0"
# define HEXA "0123456789abcdef\0"
# define NUMBS "0123456789\0"
# define FLAGS "+ #-0.*\0"

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_settings{
	int		width;
	int		precision;
	int		ccount;
	bool	minus;
	bool	dot;
	bool	zero;
	bool	asterisk;
	bool	dotastrsk;
	bool	negative;
	bool	pound;
	bool	plus;
	bool	space;
	bool	nzero;
}		t_settings;

int		ft_printf(const char *format, ...);
int		ft_writeconv_string(char *s, t_settings *sets);
int		ft_write_char(char c, t_settings *sets);
int		ft_isbigger(int a, int b);
void	ft_init_struct(t_settings *sets);
int		ft_write_int(long i, t_settings *sets);
char	*ft_uitoa(unsigned int n);
int		ft_write_uint(unsigned int i, t_settings *sets);
char	*ft_uint_to_hexa(unsigned long x);
int		ft_write_hexa(unsigned int i, t_settings *sets, char fmt);
void	ft_putzeros(int len);
void	ft_putblanks(int len);
char	*ft_putblanks_two(char *s, int len);
int		ft_write_pointer(unsigned long i, t_settings *sets);
int		ft_handle_ints(char fmt, va_list *ap, t_settings *sets);
int		ft_handle_strings(va_list *ap, t_settings *sets);
void	ft_handle_dotflag(char *format, va_list *ap, t_settings *sets);
int		ft_writeconv_int(long c, char fmt, t_settings *sets);
int		ft_myputchar(char format, int *count);
char	*ft_add_zeros(char *s, int *len, t_settings *sets);
char	*ft_add_spaces_after(char *s, int len);
char	*ft_add_spaces(char *s, int len);
char	*ft_int_precision(char *s, t_settings *sets, int *len, int i);
char	*freejoin(char *s1, char *s2);
char	*free_substr(char *s1, int p);
void	*loc_calloc(size_t count, size_t size, char c);
char	*ft_spaces_or_zeros(char *nstr, int *len, t_settings *sets);
int		ft_print_pct(t_settings *sets);

#endif
