/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:26:19 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/27 18:33:51 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

void	argument_analize(t_argc *params, va_list ap)
{
	if ((*params).specifier == 's' && (*params).length[0] != 'l')
		s_analizator(params, ap);
	else if ((*params).specifier == 'S' || ((*params).specifier == 's'
		&& (*params).length[0] == 'l'))
		us_analizator(params, ap);
	else if ((*params).specifier == 'd' || (*params).specifier == 'i'
		|| (*params).specifier == 'D')
		d_analizator(params, ap);
	else if ((*params).specifier == 'o' || (*params).specifier == 'O')
		o_analizator(params, ap);
	else if ((*params).specifier == 'u' || (*params).specifier == 'U')
		u_analizator(params, ap);
	else if ((*params).specifier == 'x' || (*params).specifier == 'X'
		|| (*params).specifier == 'p')
		x_analizator(params, ap);
	else if ((*params).specifier == 'c' && (*params).length[0] != 'l')
		c_analizator(params, ap);
	else if ((*params).specifier == 'C' || ((*params).specifier == 'c'
		&& (*params).length[0] == 'l'))
		uc_analizator(params, ap);
	else if ((*params).specifier == 'f' || (*params).specifier == 'F')
		f_analizator(params, ap);
	else if ((*params).specifier == 'n')
		n_analizator(params, ap);
}

void	check_star_anywhere(char c, int *i, int *param)
{
	if (c == '*')
	{
		*param = '*';
		(*i)++;
	}
}

void	argument_save(char *argv, t_argc *params, va_list ap)
{
	int i;

	i = 0;
	check_star_anywhere(argv[i], &i, &params->width);
	check_flags(argv, &i, (*params).flag);
	check_star_anywhere(argv[i], &i, &params->width);
	if ((argv[i] >= '0' && argv[i] <= '9'))
	{
		(*params).star_width = (*params).width;
		(*params).width = ft_atoi(&argv[i]);
		while (argv[i] >= '0' && argv[i] <= '9')
			i++;
	}
	check_star_anywhere(argv[i], &i, &params->width);
	precision_finder(argv, &i, params);
	check_star_anywhere(argv[i], &i, &params->width);
	check_length(&argv[i], &i, (*params).length);
	check_star_anywhere(argv[i], &i, &params->width);
	specifier_finder(params, argv, &i, ap);
	if (!(*params).left)
		while (argv[i])
		{
			write(1, &argv[i++], 1);
			(*params).res++;
		}
}

void	struct_init(t_argc *params)
{
	int i;

	i = 0;
	(*params).one_arg = NULL;
	while (i < FLAG_LIMIT)
		(*params).flag[i++] = 0;
	(*params).width = 0;
	(*params).star_width = 0;
	(*params).precision = -1;
	(*params).length[0] = 0;
	(*params).length[1] = 0;
	(*params).length[2] = 0;
	(*params).specifier = 0;
	(*params).left = NULL;
	(*params).left_len = 0;
	(*params).reserve = NULL;
	(*params).sign = 0;
}

int		ft_printf(const char *format, ...)
{
	int			i;
	va_list		ap;
	t_argc		params;

	i = 0;
	params.res = 0;
	va_start(ap, format);
	while (format[i] && format[i] != '%')
		write(1, &format[i++], 1);
	params.res += i;
	while (format[i])
	{
		if (format[i] == '%' && !if_percent_found(format, &params, &i))
			continue;
		while (format[i] && format[i] != '%')
		{
			write(1, &format[i++], 1);
			params.res++;
		}
		if (params.one_arg)
			argument_save(params.one_arg, &params, ap);
		ft_strdel(&params.left);
		ft_strdel(&params.one_arg);
	}
	va_end(ap);
	return (params.res);
}
