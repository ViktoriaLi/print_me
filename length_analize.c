/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:15:35 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 16:39:50 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_length_hhll(int h_count, int l_count, char **dest)
{
	if (h_count % 2 != 0 && (*dest)[0] != 'l' && (*dest)[0] != 'z'
		&& (*dest)[0] != 'j')
	{
		(*dest)[0] = 'h';
		(*dest)[1] = 0;
	}
	if (l_count % 2 != 0 && (*dest)[0] != 'l' && (*dest)[0] != 'z'
		&& (*dest)[0] != 'j')
	{
		(*dest)[0] = 'l';
		(*dest)[1] = 0;
	}
}

void	check_length_hlzj(int *j, int len, char *length, char **dest)
{
	int h_count;
	int l_count;

	h_count = 0;
	l_count = 0;
	while (*j < len)
	{
		if (length[*j] == 'z')
		{
			(*dest)[0] = 'z';
			(*dest)[1] = 0;
		}
		if (length[*j] == 'j' && (*dest)[0] != 'z')
		{
			(*dest)[0] = 'j';
			(*dest)[1] = 0;
		}
		if (length[*j] == 'h')
			h_count++;
		if (length[*j] == 'l')
			l_count++;
		(*j)++;
	}
	check_length_hhll(h_count, l_count, dest);
}

void	check_length(char *length, int *i, char *dest)
{
	int j;
	int len;

	j = 0;
	len = 0;
	while (length[len] == 'h' || length[len] == 'l' || length[len] == 'j'
		|| length[len] == 'z')
	{
		len++;
		(*i)++;
	}
	if (ft_len_strnstr(length, "ll", len) && dest[0] != 'z' && dest[0] != 'j')
	{
		dest[0] = 'l';
		dest[1] = 'l';
	}
	if (ft_len_strnstr(length, "hh", len) && dest[0] != 'l' &&
		dest[0] != 'z' && dest[0] != 'j')
	{
		dest[0] = 'h';
		dest[1] = 'h';
	}
	check_length_hlzj(&j, len, length, &dest);
}

void	u_depend_length(uintmax_t *d, char *length, t_argc *params)
{
	if ((ft_strcmp(length, "hh") == 0) && (*params).specifier == 'u')
		*d = (unsigned char)*d;
	else if (ft_strcmp(length, "ll") == 0)
		*d = (unsigned long long)*d;
	else if (length[0] == 'h' && (*params).specifier == 'u')
		*d = (unsigned short)*d;
	else if (length[0] == 'l')
		*d = (unsigned long)*d;
	else if (length[0] == 'z')
		*d = (size_t)*d;
	else if (length[0] == 'j')
		*d = (uintmax_t)*d;
	else
	{
		if ((*params).specifier == 'U')
			*d = (unsigned long)*d;
		else
			*d = (unsigned int)*d;
	}
}
