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
	k = 0;
	if (if_flag(tmp, '+', j))
		flag[k++] = '+';
	if (if_flag(tmp, '#', j))
		flag[k++] = '#';
	if (if_flag(tmp, '0', j))
		flag[k++] = '0';
	if (if_flag(tmp, '-', j))
		flag[k++] = '-';
	if (if_flag(tmp, ' ', j))
		flag[k++] = ' ';
	if (if_flag(tmp, '\'', j))
		flag[k++] = '\'';
	if (tmp)
		free(tmp);
}

int		check_specifier(char type)
{
	if (type == 's' || type == 'S' || type == 'p' || type == 'd' || type == 'D'
	|| type == 'i' || type == 'o' || type == 'O' || type == 'u' || type == 'U'
	|| type == 'x' || type == 'X' || type == 'c' || type == 'C'/* || type == 'e'
	|| type == 'E' || type == 'f' || type == 'F' || type == 'g' || type == 'G'
	|| type == 'a' || type == 'A' || type == 'n'*/)
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
		(*params).left = (char *)malloc(*i - len + 1);
		(*params).left[*i - len] = 0;
		j = *i - len;
		(*params).left_len = j;
		while (*i >= len)
			(*params).left[j--] = argv[(*i)--];
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
	while (format[*i] && format[(*i)] != '%')
	{
		(*i)++;
		j++;
	}
	if (format[*i] == '%')
		(*params).specifier = '%';
	len = (*i)--;
	(*params).one_arg = (char *)malloc(j + 1);
	(*params).one_arg[j--] = 0;
	while (j >= 0)
		(*params).one_arg[j--] = format[(*i)--];
	(*i) = len;
	return (1);
}
