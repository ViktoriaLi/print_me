#include "ft_printf.h"

void print_hex_and_oct(unsigned int nbr, t_argc params, int base)
{
if (nbr >= base)
  print_hex_and_oct(nbr / base, params, base);
if ((nbr % base) < 10)
  ft_putchar((nbr % base) + 48);
else if (params.specifier == 'x')
  ft_putchar((nbr % base) - 10 + 97);
else if (params.specifier == 'X')
	ft_putchar((nbr % base) - 10 + 65);
}
