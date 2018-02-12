#include "ft_printf.h"
#include <stdio.h>

static void		print_chars(intmax_t d, intmax_t c, intmax_t n)
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

void			ft_put_long_nbr(intmax_t n)
{
	intmax_t		d;
	intmax_t		c;

	c = 1;
	d = n;
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

/*int main(void)
{
	ft_put_long_nbr(18446744073709551574);
	write(1, "\n", 1);
	ft_put_long_nbr(-9223372036854775808);
	write(1, "\n", 1);
	ft_put_long_nbr(4294967295);
	write(1, "\n", 1);
	ft_put_long_nbr(4294967296);
	write(1, "\n", 1);

}*/

static void		print_uns_chars(uintmax_t d, uintmax_t c, uintmax_t n)
{
	char res;

	res = 0;
	while (d > 9)
	{
		d = d / 10;
		c = c * 10;
	}
	while (c > 0)
	{
		res = (n / c) % 10 + '0';
		write(1, &res, 1);
		c = c / 10;
	}
}

void			ft_put_uns_long_nbr(uintmax_t n)
{
	uintmax_t		d;
	uintmax_t		c;

	c = 1;
	if (n > 9223372036854775807)
	{
		write(1, "-", 1);
	}
	d = n;
	print_uns_chars(d, c, n);
}
