/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:37:44 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/22 16:37:48 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precision_finder(char *argv, int *i, t_argc *params)
{
	if (argv[*i] == '.')
	{
		(*params).precision = 0;
		(*i)++;
		check_star_anywhere(argv[*i], i, &params->precision);
		if (argv[*i] >= '0' && argv[*i] <= '9')
		{
			if ((*params).precision != '*')
				(*params).precision = ft_atoi(&argv[*i]);
			else if ((*params).width != '*')
				(*params).width = ft_atoi(&argv[*i]);
		}
		while ((argv[*i] >= '0' && argv[*i] <= '9'))
			(*i)++;
	}
	else if (argv[*i] == '.')
		(*i)++;
}

int		check_specifier(char type)
{
	if (type == 's' || type == 'S' || type == 'p' || type == 'd' || type == 'D'
	|| type == 'i' || type == 'o' || type == 'O' || type == 'u' || type == 'U'
	|| type == 'x' || type == 'X' || type == 'c' || type == 'C' || type == 'f'
	|| type == 'F' || type == 'n'/* || type == 'e'
	|| type == 'E'  || type == 'g' || type == 'G'
	|| type == 'a' || type == 'A' */)
		return (type);
	else
		return (0);
}

void	specifier_finder(t_argc *params, char *argv, int *i, va_list ap)
{
	int len;
	int j;

	j = 0;
	len = 0;
	if (check_specifier(argv[*i]))
	{
		(*params).specifier = argv[(*i)++];
		len = *i;
		while (argv[*i])
			(*i)++;
		j = *i - len;
		params->left = ft_strsub(argv, len, j);
		(*params).left_len = j;
		argument_analize(params, ap);
		(*i)++;
	}
	else if ((*params).specifier == '%' || ((argv[*i] >= 65
		&& argv[*i] <= 90) || (argv[*i] >= 97 && argv[*i] <= 122)))
	{
		if ((*params).specifier != '%')
			(*params).specifier = argv[(*i)++];
		c_analizator(params, ap);
	}
}

int		if_percent_found(const char *format, t_argc *params, int *i)
{
	int j;
	int len;

	j = 0;
	len = 0;
	struct_init(params);
	if (format[++(*i)] == '%')
	{
		write(1, &format[(*i)++], 1);
		(*params).res++;
		return (0);
	}
	j = (*i);
	while (format[*i] && format[(*i)] != '%')
		(*i)++;
	j = (*i) - j;
	if (format[*i] == '%')
		(*params).specifier = '%';
	len = (*i)--;
	(*params).one_arg = ft_strsub(format, ((*i) - j + 1), j);
	(*i) = len;
	return (1);
}
