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
# include "libft/libft.h"

typedef struct	s_argc
{
	char *one_arg;
	char flag;
  int width;
  int precision;
  char length[3];
  char specifier;
	char *left;
}				       t_argc;

int ft_printf(const char *format, ...);
size_t		ft_strlen(const char *s);
void			ft_putnbr(int n);

void s_analizator(t_argc params, va_list ap);
void S_analizator(t_argc params, va_list ap);
void p_analizator(t_argc params, va_list ap);
void d_analizator(t_argc params, va_list ap);
void D_analizator(t_argc params, va_list ap);
void i_analizator(t_argc params, va_list ap);
void o_analizator(t_argc params, va_list ap);
void O_analizator(t_argc params, va_list ap);
void u_analizator(t_argc params, va_list ap);
void U_analizator(t_argc params, va_list ap);
void x_analizator(t_argc params, va_list ap);
void X_analizator(t_argc params, va_list ap);
void c_analizator(t_argc params, va_list ap);
void C_analizator(t_argc params, va_list ap);

#endif
