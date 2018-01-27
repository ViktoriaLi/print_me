#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void print_hex_x(unsigned int nbr)
{
if (nbr >= 16)
  print_hex_x(nbr / 16);
if ((nbr % 16) < 10)
  ft_putchar((nbr % 16) + 48);
else
  ft_putchar((nbr % 16) - 10 + 97);
}

void print_hex_X(unsigned int nbr)
{
if (nbr >= 16)
  print_hex_X(nbr / 16);
if ((nbr % 16) < 10)
  ft_putchar((nbr % 16) + 48);
else
  ft_putchar((nbr % 16) - 10 + 65);
}

void print_hex_o(unsigned int nbr)
{
if (nbr >= 8)
  print_hex_o(nbr / 8);
if ((nbr % 8) < 10)
  ft_putchar((nbr % 8) + 48);
}

void print_hex_O(unsigned int nbr)
{
  if (nbr >= 8)
    print_hex_O(nbr / 8);
  if ((nbr % 8) < 10)
    ft_putchar((nbr % 8) + 48);
  }
