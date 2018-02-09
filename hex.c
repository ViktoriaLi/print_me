#include "ft_printf.h"
#include <stdio.h>

int print_oct(unsigned int nbr, t_argc params, unsigned int base)
{
	static int res;

	res = 0;
	if (nbr >= base)
  		print_oct(nbr / base, params, base);
	if ((nbr % base) < 10)
			res = res * 10 + (nbr % base);
	return (res);
}

char *print_hex(unsigned int nbr, t_argc params, unsigned int base, int count)
{
	static char *res;
	static int i;

	i = 0;
	res = NULL;
	res = (char *)malloc(count + 1);
	if (nbr >= base)
		print_hex(nbr / base, params, base, count);
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
	res[i] = 0;
	return (res);
}
