#include "ft_printf.h"
#include <stdio.h>

int print_oct(unsigned long long nbr, unsigned int base)
{
	static int res;

	res = 0;
	/*while (nbr >= base)
	{
		res = res * 10 + (nbr % base);
		nbr = nbr / base;
	}*/
	if (nbr >= base)
  		print_oct(nbr / base, base);
	if ((nbr % base) < 10)
			res = res * 10 + (nbr % base);
	return (res);
}

void print_hex(unsigned long long nbr, t_argc params, unsigned int base)
{
	if (nbr >= base)
		print_hex(nbr / base, params, base);
	if ((nbr % base) < 10)
	{
      ft_putchar((nbr % base) + 48);
	}
	else if (params.specifier == 'x' || params.specifier == 'p')
	{
    ft_putchar((nbr % base) - 10 + 97);
	}
	else if (params.specifier == 'X')
	{
    ft_putchar((nbr % base) - 10 + 65);
	}
}
