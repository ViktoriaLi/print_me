/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:40:26 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 16:41:08 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	if (s1[i] != s2[i])
		return (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void		ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			write(1, &(*(s + i)), 1);
			i++;
		}
	}
}

void		ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!s || start > ft_strlen(s) || !(dest = (char *)malloc(sizeof(char) *
		(len + 1))))
		return (NULL);
	while (i < len && s[start] != 0)
	{
		dest[i] = (char)s[start];
		i++;
		start++;
	}
	dest[i] = 0;
	return (dest);
}
