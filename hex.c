/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:53:20 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/22 16:54:41 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char	*print_hex(uintmax_t nbr, t_argc params, unsigned int base, int count)
{
	static char		*res;
	static int		i;

	i = 0;
	res = NULL;
	res = (char *)malloc(count + 1);
	while (i < count)
		res[i++] = 0;
	i = 0;
	if (nbr >= base)
		print_hex(nbr / base, params, base, count);
	if ((nbr % base) < 10)
		res[i++] = (nbr % base) + 48;
	else if (params.specifier == 'x' || params.specifier == 'p')
		res[i++] = (nbr % base) - 10 + 97;
	else if (params.specifier == 'X')
		res[i++] = (nbr % base) - 10 + 65;
	return (res);
}

int		print_unicode(wchar_t *test, int len, t_argc *params)
{
	int i;
	int j;
	int bytes_count;
	int code;
	int count;
	char res[4];
	unsigned int first[4];
	int shift;

	i = 0;
	j = 0;
	code = 0;
	bytes_count = 0;
	count = 0;
	while (test[i] && i < len)
	{
		if (test[i] <= 127)
		{
			if ((count + 1) <= len)
			{
				write(1, &test[i], 1);
				count++;
			}
		}
		else
		{
			j = 0;
			bytes_count = 0;
			if (test[i] > 127 && test[i] <= 2047)
			{
				j = 0;
				bytes_count = 2;
				shift = 6;
				while (j < bytes_count)
				{
					first[j] = test[i];
					j++;
				}
				j = 0;
				while (j < bytes_count)
				{
					res[j] = first[j] >> shift;
					if (j == 0)
						{
							res[j] = res[j] & 31;
							res[j] += 192;
						}
					else
					{
						res[j] = res[j] & 63;
						res[j] += 128;
					}
					shift -= 6;
					j++;
				}
				if ((count + bytes_count) <= len)
				{
					write(1, res, bytes_count);
					count += 2;
				}
			}
			else if (test[i] > 2047 && test[i] <= 65535)
			{
				j = 0;
				bytes_count = 3;
				shift = 12;
				while (j < bytes_count)
				{
					first[j] = test[i];
					j++;
				}
				j = 0;
				while (j < bytes_count)
				{
					res[j] = first[j] >> shift;
					if (j == 0)
						{
							res[j] = res[j] & 15;
							res[j] += 224;
						}
					else
					{
						res[j] = res[j] & 63;
						res[j] += 128;
					}
					shift -= 6;
					j++;
				}
				if ((count + bytes_count) <= len)
				{
					write(1, res, bytes_count);
					count += 3;
				}
			}
			else if (test[i] > 65535 && test[i] <= 1114111)
			{
				j = 0;
				bytes_count = 4;
				shift = 18;
				while (j < bytes_count)
				{
					first[j] = test[i];
					j++;
				}
				j = 0;
				while (j < bytes_count)
				{
					res[j] = first[j] >> shift;
					if (j == 0)
						{
							res[j] = res[j] & 7;
							res[j] += 240;
						}
					else
					{
						res[j] = res[j] & 63;
						res[j] += 128;
					}
					shift -= 6;
					j++;
				}
				if ((count + bytes_count) <= len)
				{
					write(1, res, bytes_count);
					count += 4;
				}
			}
		}
		i++;
	}
	if ((*params).specifier != 'C' && (*params).specifier != 'c')
		(*params).res -= count - len;
	return (0);
}
