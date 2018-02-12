#include "ft_printf.h"
#include <stdio.h>

uintmax_t print_oct(uintmax_t nbr, unsigned int base)
{
	static uintmax_t res;
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
	//printf("111 %jd\n", res);
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

char *print_hex(uintmax_t nbr, t_argc params, unsigned int base)
{
	static char *res;
	static uintmax_t i;

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

void long_print_params_left(uintmax_t d, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && (*params).specifier
    != 'u' && (*params).specifier != 'U' && !if_flag((*params).flag, '+', FLAG_LIMIT)
    && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
  }
  if (if_flag((*params).flag, '+', FLAG_LIMIT) && (*params).specifier != 'o' && (*params).specifier != 'O'
  && (*params).specifier != 'u' && (*params).specifier != 'U')
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
	if (d == 9223372036854775807 && ((*params).specifier == 'o' || (*params).specifier == 'O'))
	 	write(1, "777777777777777777777", 21);
	else
		ft_put_uns_long_nbr(d);
  if (spaces > 0)
  {
    (*params).res += spaces;
    while (spaces--)
    {
      write(1, " ", 1);
    }
  }
}

void long_print_params_right(uintmax_t d, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && !if_flag((*params).flag, '+', FLAG_LIMIT)
  && (*params).specifier != 'u' && (*params).specifier != 'U' &&
  (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
		if (if_flag((*params).flag, '0', FLAG_LIMIT))
      zeros -= 1;
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
      && (*params).specifier != 'o' && (*params).specifier != 'O'
      && (*params).specifier != 'u' && (*params).specifier != 'U')
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
	if (d == 9223372036854775807 && ((*params).specifier == 'o' || (*params).specifier == 'O'))
  	write(1, "777777777777777777777", 21);
	else
		ft_put_uns_long_nbr(d);
}

/*void print_uint_params_left(uintmax_t d, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && d >= 0 && (*params).specifier
    != 'u' && (*params).specifier != 'U' && !if_flag((*params).flag, '+', FLAG_LIMIT)
    && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
  }
  if (d >= 0 && if_flag((*params).flag, '+', FLAG_LIMIT) && (*params).specifier != 'o' && (*params).specifier != 'O'
  && (*params).specifier != 'u' && (*params).specifier != 'U')
  {
    (*params).res += 1;
    spaces -= 1;
    //zeros -= 1;
    write(1, "+", 1);
  }
  if (d < 0 && zeros > 0)
  {
      spaces--;
      write(1, "-", 1);
      d = d * (-1);
      zeros += 1;
      //(*params).res += 1;
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
  {
    if (d == 18446744073709551615)
      ft_put_uns_long_nbr(d);
    else if (d >= -9223372036854775807 && d <= 9223372036854775807)
      ft_put_long_nbr(d);
    else
      ft_put_uns_long_nbr(d);
  }
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
  if (if_flag((*params).flag, ' ', FLAG_LIMIT)  &&
    !if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '+', FLAG_LIMIT)
  && (*params).specifier != 'u' && (*params).specifier != 'U' &&
  (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
  }
  if (d >= 0 && if_flag((*params).flag, '+', FLAG_LIMIT) && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    spaces -= 1;
    if ((*params).precision <= 0)
      zeros -= 1;
  }
  if (spaces > 0 && zeros > 0)
  {
    if (d < 0 && zeros > 0)
      spaces--;
    (*params).res += spaces;
    while (spaces--)
      write(1, " ", 1);
  }
  if (d >= 0 && if_flag((*params).flag, '+', FLAG_LIMIT)
      && (*params).specifier != 'o' && (*params).specifier != 'O'
      && (*params).specifier != 'u' && (*params).specifier != 'U')
  {
    (*params).res += 1;
    write(1, "+", 1);
  }
  if (spaces > 0 && zeros <= 0)
  {
    if (d < 0 && zeros > 0)
      spaces--;
    (*params).res += spaces;
    while (spaces--)
      write(1, " ", 1);
  }
  if (d < 0 && zeros > 0)
  {
      write(1, "-", 1);
      d = d * (-1);
      if ((*params).precision > 0 && !if_flag((*params).flag, '0', FLAG_LIMIT))
        zeros += 1;
  }
  if (zeros > 0)
  {
    (*params).res += zeros;
    while (zeros--)
      write(1, "0", 1);
  }
  if (((*params).specifier == 'o' || (*params).specifier == 'O') && if_flag((*params).flag, '#', FLAG_LIMIT))
    write(1, "0", 1);
  //printf("DDD %jud\n", d);
  if (d != 0)
  {
    if (d == 18446744073709551615)
      ft_put_uns_long_nbr(d);
    else if (d >= -9223372036854775807 && (uintmax_t)d <= 9223372036854775807)
      ft_put_long_nbr(d);
    else
      ft_put_uns_long_nbr(d);
  }
  else
    if ((*params).precision != 0)
      write(1, "0", 1);
}*/
