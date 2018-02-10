#include "ft_printf.h"
#include <stdio.h>

int print_oct(unsigned int nbr, unsigned int base)
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

void print_hex(uintmax_t nbr, t_argc params, unsigned int base)
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

void print_uint_params_left(uintmax_t d, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && (*params).specifier
    != 'u' && (*params).specifier != 'U' && !if_flag((*params).flag, '+', FLAG_LIMIT)
    && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
  }
  if (if_flag((*params).flag, '+', FLAG_LIMIT) && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    spaces -= 1;
    //zeros -= 1;
    write(1, "+", 1);
  }
  if (zeros > 0)
  {
    (*params).res += zeros;
    while (zeros--)
      write(1, "0", 1);
  }
  if (((*params).specifier == 'o' || (*params).specifier == 'O') && if_flag((*params).flag, '#', FLAG_LIMIT))
    write(1, "0", 1);
  if (d != 0)
    ft_putnbr(d);
  else
    if ((*params).precision != 0)
      write(1, "0", 1);
  if (spaces > 0)
  {
    (*params).res += spaces;
    while (spaces--)
    {
      write(1, " ", 1);
    }
  }
}

void print_uint_params_right(uintmax_t d, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) &&
    !if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '+', FLAG_LIMIT)
  && (*params).specifier != 'u' && (*params).specifier != 'U' &&
  (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
  }
  if (if_flag((*params).flag, '+', FLAG_LIMIT) && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    spaces -= 1;
    if ((*params).precision <= 0)
      zeros -= 1;
  }
  if (spaces > 0 && zeros > 0)
  {
    (*params).res += spaces;
    while (spaces--)
      write(1, " ", 1);
  }
  if (if_flag((*params).flag, '+', FLAG_LIMIT)
      && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, "+", 1);
  }
  if (spaces > 0 && zeros <= 0)
  {
    (*params).res += spaces;
    while (spaces--)
      write(1, " ", 1);
  }
  if (zeros > 0)
  {
    (*params).res += zeros;
    while (zeros--)
      write(1, "0", 1);
  }
  if (((*params).specifier == 'o' || (*params).specifier == 'O') && if_flag((*params).flag, '#', FLAG_LIMIT))
    write(1, "0", 1);
  if (d != 0)
    ft_putnbr(d);
  else
    if ((*params).precision != 0)
      write(1, "0", 1);
}
