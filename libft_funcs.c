#include "ft_printf.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	if (s1[i] != s2[i])
		return (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

static int	main_atoi(const char *str, int i, int sign)
{
	long long	tmp;
	long long	res;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = res * 10 + sign * (str[i] - '0');
		if (tmp / 10 != res && sign == -1)
			return (0);
		if (tmp / 10 != res && sign == 1)
			return (-1);
		res = tmp;
		i++;
	}
	return (int)(res);
}

int			ft_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (main_atoi(str, i, sign));
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

size_t		ft_strlen_wide(wchar_t *s)
{
	size_t i;
	size_t res;

	i = 0;
	res = 0;
	while (s[i] != 0)
	{
		if (s[i] <= 127)
			res++;
		else if (s[i] > 127 && s[i] <= 2047)
			res += 2;
		else if (s[i] > 2047 && s[i] <= 65535)
			res += 3;
		else if (s[i] > 65535 && s[i] <= 1114111)
			res += 4;
		i++;
	}
	return (res);
}

void	ft_putstr(char const *s)
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static char		*ft_negative_itoa(intmax_t n, char *dest)
{
	size_t	d;
	intmax_t		len;

	len = 2;
	d = -1 * n;
	while (d > 9)
	{
		d = d / 10;
		len++;
	}
	d = -1 * n;
	if (!(dest = (char *)malloc((len + 1))))
		return (NULL);
	dest[len--] = 0;
	while (len)
	{
		dest[len--] = d % 10 + '0';
		d = d / 10;
	}
	dest[len] = '-';
	return (dest);
}

char			*ft_itoa(intmax_t n)
{
	size_t	d;
	intmax_t		len;
	char	*dest;

	dest = NULL;
	if (n < 0)
		return (ft_negative_itoa(n, dest));
	len = 1;
	d = n;
	while (d > 9)
	{
		d = d / 10;
		len++;
	}
	if (!(dest = (char *)malloc((len + 1))))
		return (NULL);
	dest[len--] = 0;
	while (len >= 0)
	{
		dest[len--] = n % 10 + '0';
		n = n / 10;
	}
	return (dest);
}

char			*ft_uns_itoa(uintmax_t n)
{
	uintmax_t	d;
	intmax_t		len;
	char	*dest;

	dest = NULL;
	len = 1;
	d = n;
	while (d > 9)
	{
		d = d / 10;
		len++;
	}
	if (!(dest = (char *)malloc((len + 1))))
		return (NULL);
	dest[len--] = 0;
	while (len >= 0)
	{
		dest[len--] = n % 10 + '0';
		n = n / 10;
	}
	return (dest);
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

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}
