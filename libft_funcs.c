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

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != 0)
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = (char)src[i];
	return (dst);
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

static void		print_chars(int d, int c, int n)
{
	char res;

	res = 0;
	while (d > 9)
	{
		d = d / 10;
		c = c * 10;
	}
	while (c > 0 && n >= 0)
	{
		res = (n / c) % 10 + '0';
		write(1, &res, 1);
		c = c / 10;
	}
}

void			ft_putnbr(int n)
{
	int		d;
	int		c;

	c = 1;
	if (n == -2147483648)
	{
		d = 147483648;
		n = 147483648;
		write(1, "-2", 2);
	}
	if (n < 0)
	{
		d = -1 * n;
		n = -1 * n;
		write(1, "-", 1);
	}
	else
		d = n;
	print_chars(d, c, n);
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

static char		*min_int(int n, char *dest)
{
	int		len;

	len = 3;
	n = 214748364;
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	n = 214748364;
	if (!(dest = (char *)malloc((len + 1))))
		return (NULL);
	dest[len--] = 0;
	dest[len--] = '8';
	while (len >= 2)
	{
		dest[len--] = n % 10 + '0';
		n = n / 10;
	}
	dest[len--] = '2';
	dest[len] = '-';
	return (dest);
}

static char		*ft_negative_itoa(long long n, char *dest)
{
	long long	d;
	int		len;

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

char			*ft_itoa(long long n)
{
	long long	d;
	int		len;
	char	*dest;

	dest = NULL;
	if (n == -2147483648)
		return (min_int(n, dest));
	if (n < 0 && n != -2147483648)
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
