/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:50:58 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 16:13:54 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	c_printing(t_argc *params, t_forprint *elems, char c)
{
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
	{
		write(1, &c, 1);
		if ((*params).width > 1)
			while ((*elems).spaces--)
				write(1, " ", 1);
	}
	else
	{
		if ((*params).width > 1 && !if_flag((*params).flag, '0', FLAG_LIMIT))
			while ((*elems).spaces--)
				write(1, " ", 1);
		else if ((*params).width > 1 &&
			if_flag((*params).flag, '0', FLAG_LIMIT))
			while ((*elems).spaces--)
				write(1, "0", 1);
		write(1, &c, 1);
	}
}

void	c_analizator(t_argc *params, va_list ap)
{
	unsigned char	c;
	t_forprint		elems;

	elems_init(&elems);
	check_stars(params, ap);
	if ((*params).specifier == 'c')
		c = va_arg(ap, int);
	else
		c = (*params).specifier;
	(*params).res += 1;
	if ((*params).width > 1)
	{
		elems.spaces = (*params).width - 1;
		(*params).res += elems.spaces;
	}
	c_printing(params, &elems, c);
	print_left(params);
}

void	uc_printing(t_argc *params, t_forprint *elems, wchar_t uc)
{
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
	{
		print_unicode(&uc, (*elems).len, params);
		if ((*params).width > (*elems).len)
			while ((*elems).spaces--)
				write(1, " ", 1);
	}
	else
	{
		if ((*params).width > (*elems).len &&
			!if_flag((*params).flag, '0', FLAG_LIMIT))
			while ((*elems).spaces--)
				write(1, " ", 1);
		else if ((*params).width > (*elems).len &&
			if_flag((*params).flag, '0', FLAG_LIMIT))
			while ((*elems).spaces--)
				write(1, "0", 1);
		print_unicode(&uc, (*elems).len, params);
	}
}

void	uc_analizator(t_argc *params, va_list ap)
{
	t_forprint	elems;
	wchar_t		uc;

	elems_init(&elems);
	check_stars(params, ap);
	uc = va_arg(ap, wchar_t);
	if (uc <= 127)
		elems.len = 1;
	else
		elems.len = ft_strlen_wide(&uc);
	(*params).res += elems.len;
	if ((*params).width > elems.len)
	{
		elems.spaces = (*params).width - elems.len;
		(*params).res += elems.spaces;
	}
	uc_printing(params, &elems, uc);
	print_left(params);
}
