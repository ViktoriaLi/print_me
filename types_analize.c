#include "ft_printf.h"
#include <stdio.h>

int if_flag(int *all_flags, int flag, int j)
{
    int i;

    i = 0;
    while (i < j)
    {
      if (all_flags[i] == flag)
        return (1);
      i++;
    }
    return (0);
}

void check_stars(t_argc *params, va_list ap)
{
  if ((*params).width == '*')
    (*params).width = va_arg(ap, int);
  if ((*params).precision == '*')
    (*params).precision = va_arg(ap, int);
}

void print_int_depend_length(intmax_t d, char *length, t_argc params)
{
  if ((ft_strcmp(length, "hh") == 0) && (params.specifier == 'd' || params.specifier == 'i' || params.specifier == 'D'))
    ft_putnbr((signed char)d);
  else if ((ft_strcmp(length, "hh") == 0)  && (params.specifier == 'u' || params.specifier == 'U'))
    ft_putnbr((unsigned char)d);
  else if ((ft_strcmp(length, "h") == 0) && (params.specifier == 'd' || params.specifier == 'i' || params.specifier == 'D'))
    ft_putnbr((short)d);
  else if ((ft_strcmp(length, "h") == 0) && (params.specifier == 'u' || params.specifier == 'U'))
    ft_putnbr((unsigned short)d);
  else if ((ft_strcmp(length, "l") == 0) && (params.specifier == 'd' || params.specifier == 'i' || params.specifier == 'D'))
    ft_putnbr((long)d);
  else if ((ft_strcmp(length, "l") == 0) && (params.specifier == 'u' || params.specifier == 'U'))
    ft_putnbr((unsigned long)d);
  else if ((ft_strcmp(length, "ll") == 0) && (params.specifier == 'd' || params.specifier == 'i' || params.specifier == 'D'))
    ft_putnbr((long	long)d);
  else if ((ft_strcmp(length, "ll") == 0) && (params.specifier == 'u' || params.specifier == 'U'))
    ft_putnbr((unsigned long	long)d);
  else if (ft_strcmp(length, "z") == 0)
    ft_putnbr((size_t)d);
  else
    ft_putnbr(d);
}

void print_int_params_left(intmax_t d, t_argc params, int zeros, int spaces)
{
  if (if_flag(params.flag, ' ', FLAG_LIMIT) && d > 0 && params.specifier != 'u' && params.specifier != 'U')
  {
    write(1, " ", 1);
    spaces -= 1;
  }
  if (if_flag(params.flag, '+', FLAG_LIMIT))
  {
    spaces -= 1;
    write(1, "+", 1);
  }
  if (zeros > 0)
    while (zeros--)
      write(1, "0", 1);
  print_int_depend_length(d, params.length, params);
  if (spaces > 0)
    while (spaces--)
      write(1, " ", 1);
}

void print_int_params_right(intmax_t d, t_argc params, int zeros, int spaces)
{
  if (if_flag(params.flag, ' ', FLAG_LIMIT) && d > 0 && !if_flag(params.flag, '0', FLAG_LIMIT)
  && params.specifier != 'u' && params.specifier != 'U')
  {
    write(1, " ", 1);
    spaces -= 1;
  }
  if (if_flag(params.flag, '+', FLAG_LIMIT))
    spaces -= 1;
  if (spaces > 0 && zeros > 0)
  {
    while (spaces--)
    write(1, " ", 1);
  }
  if (if_flag(params.flag, '+', FLAG_LIMIT))
    write(1, "+", 1);
  if (spaces > 0 && zeros <= 0)
  {
    while (spaces--)
    write(1, "0", 1);
  }
  if (zeros > 0)
    while (zeros--)
      write(1, "0", 1);
  print_int_depend_length(d, params.length, params);
}

void s_analizator(t_argc params, va_list ap)
{
  char *s;
  int len;
  int spaces;

  check_stars(&params, ap);
  s = va_arg(ap, char *);
  len = ft_strlen(s);
  if (params.precision && params.precision < len)
    len = params.precision;
  if (if_flag(params.flag, '-', FLAG_LIMIT))
  {
    write(1, s, len);
    if (params.width > len)
    {
      spaces = params.width - len;
      while (spaces--)
        write(1, " ", 1);
    }
  }
  else
  {
    if (params.width > len && !if_flag(params.flag, '0', FLAG_LIMIT))
    {
      spaces = params.width - len;
      while (spaces--)
        write(1, " ", 1);
    }
    else if (params.width > len && if_flag(params.flag, '0', FLAG_LIMIT))
    {
      spaces = params.width - len;
      while (spaces--)
        write(1, "0", 1);
    }
    write(1, s, len);
  }
  if (params.left)
    ft_putstr(params.left);
}

void S_analizator(t_argc params, va_list ap)
{
  int j;
  int len;
  int spaces;
  wchar_t *S;

  j = 0;
  len = 0;
  check_stars(&params, ap);
  S = va_arg(ap, wchar_t *);
  while(S[len])
    len++;
  if (if_flag(params.flag, '-', FLAG_LIMIT))
  {
    while(S[j])
    {
      write(1, &S[j], 1);
      j += 1;
    }
    if (params.width > len)
    {
      spaces = params.width - len;
      while (spaces--)
        write(1, " ", 1);
    }
  }
  else
  {
    if (params.width > len && !if_flag(params.flag, '0', FLAG_LIMIT))
    {
      spaces = params.width - len;
      while (spaces--)
        write(1, " ", 1);
    }
    else if (params.width > len && if_flag(params.flag, '0', FLAG_LIMIT))
    {
      spaces = params.width - len;
      while (spaces--)
        write(1, "0", 1);
    }
    while(S[j])
    {
      write(1, &S[j], 1);
      j += 1;
    }
  }
  if (params.left)
    ft_putstr(params.left);
}

void p_analizator(t_argc params, va_list ap)
{
  uintmax_t d;

  check_stars(&params, ap);
  d = va_arg(ap, uintmax_t);
  print_hex_and_oct(d, params, 16);
  if (params.left)
    ft_putstr(params.left);
}

void d_analizator(t_argc params, va_list ap)
{
  intmax_t d;
  int len;
  int spaces;
  int zeros;
  zeros = 0;
  check_stars(&params, ap);
  //printf("FLAG %c\n", params.flag);
  //printf("WIDTH %d\n", params.width);
  //printf("PRECISION %d\n", params.precision);
  //printf("LENGTH %s\n", params.length);
  //printf("SPECIFIER %c\n", params.specifier);
  //printf("LEFT %s\n", params.left);
  d = va_arg(ap, intmax_t);
  printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  return (0);
  len = ft_strlen(ft_itoa(d));
  if (params.precision > 1)
    zeros = params.precision - len;
  if (zeros > 0 && params.width > 1)
    spaces = params.width - len - zeros;
  if (zeros <= 0 && params.width > 1)
    spaces = params.width - len;
  printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (if_flag(params.flag, '-', FLAG_LIMIT))
    print_int_params_left(d, params, zeros, spaces);
  else
    print_int_params_left(d, params, zeros, spaces);
  if (params.left)
    ft_putstr(params.left);
  //printf("Prec %d\n", params.precision);
  //printf("Width %d\n", params.width);
  //printf("LEN %d\n", len);

}

void o_analizator(t_argc params, va_list ap)
{
  uintmax_t d;
  //int len;
  //int spaces;
  //int zeros;

  check_stars(&params, ap);
  d = va_arg(ap, uintmax_t);
  print_hex_and_oct(d, params, 8);
  if (params.left)
    ft_putstr(params.left);
}

void x_analizator(t_argc params, va_list ap)
{
  uintmax_t d;
  //int len;
  //int spaces;
  //int zeros;

  check_stars(&params, ap);
  d = va_arg(ap, uintmax_t);
  print_hex_and_oct(d, params, 16);
  if (params.left)
    ft_putstr(params.left);
}

void c_analizator(t_argc params, va_list ap)
{
  char c;
  int spaces;

  check_stars(&params, ap);
  c = va_arg(ap, int);
  if (if_flag(params.flag, '-', FLAG_LIMIT))
  {
    write(1, &c, 1);
    if (params.width > 1)
    {
      spaces = params.width - 1;
      while (spaces--)
        write(1, " ", 1);
    }
  }
  else
  {
    if (params.width > 1 && !if_flag(params.flag, '0', FLAG_LIMIT))
    {
      spaces = params.width - 1;
      while (spaces--)
        write(1, " ", 1);
    }
    else if (params.width > 1 && if_flag(params.flag, '0', FLAG_LIMIT))
    {
      spaces = params.width - 1;
      while (spaces--)
        write(1, "0", 1);
    }
    write(1, &c, 1);
  }
  if (params.left)
    ft_putstr(params.left);
}

void C_analizator(t_argc params, va_list ap)
{
  //int len;
  int spaces;
  //int zeros;
  wchar_t C;

  check_stars(&params, ap);
  C = va_arg(ap, wchar_t);
  if (if_flag(params.flag, '-', FLAG_LIMIT))
  {
    write(1, &C, 1);
    if (params.width > 1)
    {
      spaces = params.width - 1;
      while (spaces--)
        write(1, " ", 1);
    }
  }
  else
  {
    if (params.width > 1 && !if_flag(params.flag, '0', FLAG_LIMIT))
    {
      spaces = params.width - 1;
      while (spaces--)
        write(1, " ", 1);
    }
    else if (params.width > 1 && if_flag(params.flag, '0', FLAG_LIMIT))
    {
      spaces = params.width - 1;
      while (spaces--)
        write(1, "0", 1);
    }
    write(1, &C, 1);
  }
  if (params.left)
    ft_putstr(params.left);
}
