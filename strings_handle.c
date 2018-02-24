/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:57:46 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 17:02:01 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	string_printing(t_argc *params, t_forprint elems)
{
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
	{
		if ((*params).precision != 0)
			write(1, elems.s, elems.len);
		if ((*params).width > elems.len)
			while (elems.spaces--)
				write(1, " ", 1);
	}
	else
	{
		if ((*params).width > elems.len &&
			!if_flag((*params).flag, '0', FLAG_LIMIT))
			while (elems.spaces--)
				write(1, " ", 1);
		else if ((*params).width > elems.len &&
		if_flag((*params).flag, '0', FLAG_LIMIT))
			while (elems.spaces--)
				write(1, "0", 1);
		if ((*params).precision != 0)
			write(1, elems.s, elems.len);
	}
	print_left(params);
}

void	s_analizator(t_argc *params, va_list ap)
{
	t_forprint elems;

	elems_init(&elems);
	check_stars(params, ap);
	if ((*params).specifier == 's' || (*params).specifier == 'S')
		elems.s = va_arg(ap, char *);
	else
		elems.s = (*params).reserve;
	if (elems.s == NULL)
		elems.s = "(null)";
	elems.len = ft_strlen(elems.s);
	if ((*params).precision > 0 && (*params).precision < elems.len)
		elems.len = (*params).precision;
	else if ((*params).precision == 0)
		elems.len = 0;
	(*params).res += elems.len;
	if ((*params).specifier == 's' || (*params).specifier == 'S'
		|| if_flag((*params).flag, '0', FLAG_LIMIT))
		elems.spaces = (*params).width - elems.len;
	else
		elems.spaces = (*params).width - 1;
	if (elems.spaces > 0)
		(*params).res += elems.spaces;
	string_printing(params, elems);
}

void	ustring_printing(t_argc *params, t_forprint elems)
{
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
	{
		if (elems.zeros > 0)
			while (elems.zeros--)
				write(1, "0", 1);
		print_unicode(elems.us, elems.len, params);
		if (elems.spaces > 0)
			while (elems.spaces--)
				write(1, " ", 1);
	}
	else
	{
		if (elems.spaces > 0)
			while (elems.spaces--)
				write(1, " ", 1);
		if (elems.zeros > 0)
			while (elems.zeros--)
				write(1, "0", 1);
		print_unicode(elems.us, elems.len, params);
	}
}

void	us_analizator(t_argc *params, va_list ap)
{
	t_forprint elems;

	elems_init(&elems);
	check_stars(params, ap);
	elems.us = va_arg(ap, wchar_t *);
	if (elems.us == NULL)
	{
		elems.us = L"(null)";
		elems.len = 6;
	}
	else
		elems.len = ft_strlen_wide(elems.us);
	if ((*params).precision >= 0)
		elems.len = (*params).precision;
	(*params).res += elems.len;
	if (if_flag((*params).flag, '0', FLAG_LIMIT))
		elems.zeros = (*params).width - elems.len;
	elems.spaces = (*params).width - elems.len - elems.zeros;
	if (elems.spaces > 0)
		(*params).res += elems.spaces;
	if (elems.zeros > 0)
		(*params).res += elems.zeros;
	ustring_printing(params, elems);
	print_left(params);
}

char	*ft_len_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;
	int		res;

	i = 0;
	if (little[i] == 0)
		return (NULL);
	while (i < len && big[i] != 0)
	{
		res = i;
		j = 0;
		len = j + len;
		while (i + j < len && big[i + j] == little[j] && little[j] != 0 &&
			big[i + j] != 0)
			j++;
		if (little[j] == 0)
			return (little);
		else
			i++;
	}
	return (NULL);
}
