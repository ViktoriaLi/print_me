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

int	precision_finder(char *argv, int *i, t_argc *params)
{
	int j;

	j = 0;
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
		if (argv[*i] == '-')
			{
				(*i)++;
				if (!if_flag((*params).flag, '-', FLAG_LIMIT))
				{
					while ((*params).flag[j] != 0)
						j++;
					(*params).flag[j] = '-';
				}
				if (argv[*i] >= '0' && argv[*i] <= '9')
				{
					(*params).width = ft_atoi(&argv[*i]);
				}
			}
		while (((argv[*i] >= '0' && argv[*i] <= '9')))
			(*i)++;
		return (1);
	}
	return (0);
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
	else if ((!argv[*i] && (*params).specifier == '%') || (*params).length[0] != 0 || (argv[*i] >= 65
		&& argv[*i] <= 90) || (argv[*i] >= 97 && argv[*i] <= 122))
	{
		if (((argv[*i] >= 65 && argv[*i] <= 90) || (argv[*i] >= 97
			&& argv[*i] <= 122)))
					(*params).specifier = argv[(*i)++];
		c_analizator(params, ap);
	}
}

int		if_percent_found(const char *format, t_argc *params, int *i)
{
	int j;
	int len;
	char spec_symb;

	j = 0;
	len = 0;
	spec_symb = 0;
	struct_init(params);
	if (format[++(*i)] == '%')
	{
		write(1, &format[(*i)++], 1);
		(*params).res++;
		return (0);
	}
	j = (*i);
	while (format[*i] && format[(*i)] != '%')
	{
		if (format[*i] == '\r' || format[*i] == '\n' || format[*i] == '\v' ||
		format[*i] == '\t' || format[*i] == '"' || format[*i] == '\'' ||
		format[*i] == '\\' || format[*i] == '\0' || format[*i] == '?' ||
		format[*i] == '\a')
			spec_symb++;
		(*i)++;
	}
	j = (*i) - j;
	if (format[*i] == '%' && spec_symb == 0)
		(*params).specifier = '%';
	len = (*i)--;
	(*params).one_arg = ft_strsub(format, ((*i) - j + 1), j);
	(*i) = len;
	return (1);
}
