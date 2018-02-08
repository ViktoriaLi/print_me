#include "ft_printf.h"
#include <stdio.h>

int print_hex_and_oct(unsigned int nbr, t_argc params, unsigned int base)
{
	static int res;

	res = 0;
	if (nbr >= base)
  		print_hex_and_oct(nbr / base, params, base);
	if ((nbr % base) < 10)
	{
		res = res * 10 + (nbr % base);
	}
	else if (params.specifier == 'x' || params.specifier == 'p')
  		ft_putchar((nbr % base) - 10 + 97);
	else if (params.specifier == 'X')
		ft_putchar((nbr % base) - 10 + 65);
	return (res);
}
