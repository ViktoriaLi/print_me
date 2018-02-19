/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:59 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/01/12 18:02:47 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
//# include "libft.h"

# define FLAG_LIMIT 6

typedef struct	s_argc
{
	char *one_arg;
	int flag[6];
  int width;
	int star_width;
	int res;
	char length[3];
  int precision;
  char specifier;
	char *left;
	int left_len;
	char *reserve;
	char sign;
}				       t_argc;

int ft_printf(const char *format, ...);
int check_specifier(char type);
void check_length(char *length, int *i, char *dest);
void check_flags(char *str, int *i, int *flag);
void argument_analize(t_argc *params, va_list ap);
void argument_save(char *argv, t_argc *params, va_list ap);
void struct_init(t_argc *params);
void check_star_anywhere(char c, int *i, int *param);

void s_analizator(t_argc *params, va_list ap);
void S_analizator(t_argc *params, va_list ap);
void d_analizator(t_argc *params, va_list ap);
void o_analizator(t_argc *params, va_list ap);
void u_analizator(t_argc *params, va_list ap);
void x_analizator(t_argc *params, va_list ap);
void c_analizator(t_argc *params, va_list ap);
void C_analizator(t_argc *params, va_list ap);

int if_flag(int *all_flags, int flag, int j);
char *print_hex(uintmax_t nbr, t_argc params, unsigned int base, int count);
void check_stars(t_argc *params, va_list ap);
void print_int_depend_length(intmax_t *d, char *length, t_argc *params);
void print_uint_depend_length(uintmax_t *d, char *length, t_argc *params);
void print_params_left(char *s, t_argc *params, int zeros, int spaces);
void print_params_right(char *s, t_argc *params, int zeros, int spaces);
void long_print_params_right(uintmax_t d, t_argc *params, int zeros, int spaces);
void long_print_params_left(uintmax_t d, t_argc *params, int zeros, int spaces);
void print_left(t_argc *params);
void print_unicode(wchar_t *test, int len);

int		ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void	ft_putstr(char const *s);
char			*ft_itoa(intmax_t n);
void			ft_put_uns_long_nbr(uintmax_t n);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_uns_itoa(uintmax_t n);
char	*ft_len_strnstr(char *big, char *little, size_t len);
void	ft_strdel(char **as);
size_t		ft_strlen_wide(wchar_t *s);

#endif
