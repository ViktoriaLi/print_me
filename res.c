/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_and_stars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:28:02 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 16:30:18 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	elems_init(t_forprint *elems)
{
	(*elems).len = 0;
	(*elems).lenf = 0;
	(*elems).spaces = 0;
	(*elems).zeros = 0;
	(*elems).s = NULL;
	(*elems).sf = NULL;
	(*elems).us = NULL;
}

void	save_flags(int *tmp, int **flag, int j)
{
	int k;

	k = 0;
	if (if_flag(tmp, '+', j) && !if_flag(*flag, '+', j))
	{
		while ((*flag)[k] != 0)
			k++;
		(*flag)[k++] = '+';
	}
	if (if_flag(tmp, '#', j) && !if_flag(*flag, '#', j))
	{
		while ((*flag)[k] != 0)
			k++;
		(*flag)[k++] = '#';
	}
	if (if_flag(tmp, '0', j) && !if_flag(*flag, '0', j))
	{
		while ((*flag)[k] != 0)
			k++;
		(*flag)[k++] = '0';
	}
	if (if_flag(tmp, '-', j) && !if_flag(*flag, '-', j))
	{
		while ((*flag)[k] != 0)
			k++;
		(*flag)[k++] = '-';
	}

	if (if_flag(tmp, ' ', j) && !if_flag(*flag, ' ', j))
	{
		while ((*flag)[k] != 0)
			k++;
		(*flag)[k++] = ' ';
	}

	if (if_flag(tmp, '\'', j) && !if_flag(*flag, '\'', j))
	{
		while ((*flag)[k] != 0)
			k++;
		(*flag)[k++] = '\'';
	}
}

void	check_flags(char *str, int *i, int *flag)
{
	int j;
	int k;
	int *tmp;

	j = 0;
	k = 0;
	tmp = NULL;
	while (str[*i] == '+' || str[*i] == '#' || str[*i] == '0' ||
		str[*i] == '-' || str[*i] == ' ' || str[*i] == '\'')
	{
		j++;
		(*i)++;
	}
	tmp = (int *)malloc(sizeof(int) * (j + 1));
	tmp[j] = 0;
	*i = 0;
	while (k < j)
		tmp[k++] = str[(*i)++];
	save_flags(tmp, &flag, j);
	if (tmp)
		free(tmp);
}

int		if_flag(int *all_flags, int flag, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		if (all_flags[i] == flag)
			return (1);
		i++;
	}
	return (0);
}

void	check_stars(t_argc *params, va_list ap)
{
	int i;

	i = 0;
	if ((*params).star_width == '*')
		(*params).star_width = va_arg(ap, int);
	if ((*params).width == '*')
	{
		(*params).width = va_arg(ap, int);
		if ((*params).width < 0)
		{
			(*params).width = (*params).width * -1;
			if (!if_flag((*params).flag, '-', FLAG_LIMIT))
			{
				while ((*params).flag[i] != 0)
					i++;
				(*params).flag[i] = '-';
			}
		}
	}
	i = 0;
	if ((*params).precision == '*')
		(*params).precision = va_arg(ap, int);
}

void		check_specifier(char *argv, t_argc *params, int *i, va_list ap)
{
	int len;
	int j;

	j = 0;
	len = 0;
	if (argv[*i] == 's' || argv[*i] == 'S' || argv[*i] == 'p' || argv[*i] == 'd'
	|| argv[*i] == 'D' || argv[*i] == 'i' || argv[*i] == 'o' || argv[*i] == 'O'
	|| argv[*i] == 'u' || argv[*i] == 'U' || argv[*i] == 'x' || argv[*i] == 'X'
	|| argv[*i] == 'c' || argv[*i] == 'C' || argv[*i] == 'n')
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
}

void	specifier_finder(t_argc *params, char *argv, int *i, va_list ap)
{
	check_specifier(argv, params, i, ap);
	if ((!argv[*i] && (*params).specifier == '%') || (*params).specifier == 0 ||
	(*params).length[0] != 0 || (argv[*i] >= 65 && argv[*i] <= 90) ||
	(argv[*i] >= 97 && argv[*i] <= 122))
	{
		if (((argv[*i] >= 65 && argv[*i] <= 90) || (argv[*i] >= 97
			&& argv[*i] <= 122)))
				(*params).specifier = argv[(*i)++];
		c_analizator(params, ap);
	}
}
