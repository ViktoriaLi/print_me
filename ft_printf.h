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

# define FLAG_LIMIT 5

typedef struct	s_argc
{
	char *one_arg;
	int flag[5];
  int width;
	int res;
  int precision;
  char length[3];
  char specifier;
	char *left;
}				       t_argc;

int ft_printf(const char *format, ...);
int check_specifier(char type);
void check_length(char length1, char length2, char *dest);
int check_precision(char *precision);
int check_width(char *width);
void check_flags(char *str, int *i, int *flag);
void argument_analize(t_argc *params, va_list ap);
void argument_save(char *argv, t_argc *params, va_list ap);
void struct_init(t_argc *params);


void s_analizator(t_argc *params, va_list ap);
void S_analizator(t_argc *params, va_list ap);
void p_analizator(t_argc *params, va_list ap);
void d_analizator(t_argc *params, va_list ap);
void D_analizator(t_argc *params, va_list ap);
void o_analizator(t_argc *params, va_list ap);
void O_analizator(t_argc *params, va_list ap);
void u_analizator(t_argc *params, va_list ap);
void U_analizator(t_argc *params, va_list ap);
void x_analizator(t_argc *params, va_list ap);
void X_analizator(t_argc *params, va_list ap);
void c_analizator(t_argc *params, va_list ap);
void C_analizator(t_argc *params, va_list ap);

int if_flag(int *all_flags, int flag, int j);
void print_hex_and_oct(unsigned int nbr, t_argc params, unsigned int base);
void print_hex_X(unsigned int nbr);
void print_hex_o(unsigned int nbr);
void print_hex_O(unsigned int nbr);
void check_stars(t_argc *params, va_list ap);
void print_int_depend_length(intmax_t d, char *length, t_argc *params);
void print_int_params_left(intmax_t d, t_argc *params, int zeros, int spaces);
void print_int_params_right(intmax_t d, t_argc *params, int zeros, int spaces);


int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void			ft_putnbr(int n);
void	ft_putstr(char const *s);
char			*ft_itoa(int n);
void	ft_putchar(char c);

#endif
