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

/*void print_hex(unsigned long long nbr, t_argc params, unsigned int base)
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
}*/

char *print_hex(unsigned long long nbr, t_argc params, unsigned int base)
{
	static char *res;
	static int i;

	i = 0;
	res = NULL;
	res = (char *)malloc(16 + 1);
	while (i < 16)
	{
		res[i] = 0;
		i++;
	}
	i = 0;
	if (nbr >= base)
		print_hex(nbr / base, params, base);
	if ((nbr % base) < 10)
	{
			res[i] = (nbr % base) + 48;
			i++;
	}
	else if (params.specifier == 'x' || params.specifier == 'p')
	{
		res[i] = (nbr % base) - 10 + 97;
		i++;
	}
	else if (params.specifier == 'X')
	{
		res[i] = (nbr % base) - 10 + 65;
		i++;
	}
	return (res);
}
