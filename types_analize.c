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

void s_analizator(t_argc params, va_list ap)
{
  char *s;
  int len;
  int spaces;
  int prec;

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
    if (params.width > len)
    {
      spaces =  params.width - len;
      while (spaces--)
        write(1, " ", 1);
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
  int zeros;
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
    if (params.width > len)
    {
      spaces = params.width - len;
      while (spaces--)
        write(1, " ", 1);
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
  int len;
  int spaces;
  int zeros;
  check_stars(&params, ap);
}

void d_analizator(t_argc params, va_list ap)
{
  int d;
  int len;
  int spaces;
  int zeros;
  zeros = 0;
  check_stars(&params, ap);
  /*printf("FLAG %c\n", params.flag);
  printf("WIDTH %d\n", params.width);
  printf("PRECISION %d\n", params.precision);
  printf("LENGTH %s\n", params.length);
  printf("SPECIFIER %c\n", params.specifier);
  printf("LEFT %s\n", params.left);*/
  d = va_arg(ap, int);
  len = ft_strlen(ft_itoa(d));
  if (params.precision > 1)
    zeros = params.precision - len;
  if (params.flag[0] == 0)
  {
    if (zeros > 0 && params.width > 1)
      spaces = params.width - len  - zeros;
    if (zeros <= 0 && params.width > 1)
      spaces = params.width - len;
    if (spaces > 0)
      while (spaces--)
      write(1, " ", 1);
    if (zeros > 0)
      while (zeros--)
        write(1, "0", 1);
    ft_putnbr(d);
  }
  if (if_flag(params.flag, '+', FLAG_LIMIT) && !if_flag(params.flag, '-', FLAG_LIMIT))
  {
    if (zeros > 0 && params.width > 1)
      spaces = params.width - len - 1 - zeros;
    if (zeros <= 0 && params.width > 1)
      spaces = params.width - len - 1;
    if (spaces > 0)
      while (spaces--)
        write(1, " ", 1);
    write(1, "+", 1);
    if (zeros > 0)
      while (zeros--)
        write(1, "0", 1);
    ft_putnbr(d);
  }
  if (if_flag(params.flag, '-', FLAG_LIMIT) && !if_flag(params.flag, '-', FLAG_LIMIT))
  {
    if (zeros > 0 && params.width > 1)
      spaces = params.width - len - zeros;
    if (zeros <= 0 && params.width > 1)
      spaces = params.width - len;
    if (zeros > 0)
      while (zeros--)
        write(1, "0", 1);
    ft_putnbr(d);
    if (spaces > 0)
      while (spaces--)
        write(1, " ", 1);
  }
  if (if_flag(params.flag, '-', FLAG_LIMIT) && if_flag(params.flag, '+', FLAG_LIMIT))
  {
    if (zeros > 0 && params.width > 1)
      spaces = params.width - len - zeros - 1;
    if (zeros <= 0 && params.width > 1)
      spaces = params.width - len - 1;
    write(1, "+", 1);
    if (zeros > 0)
      while (zeros--)
        write(1, "0", 1);
    ft_putnbr(d);
    if (spaces > 0)
      while (spaces--)
        write(1, " ", 1);
  }
  if (params.left)
    ft_putstr(params.left);
  //printf("Prec %d\n", params.precision);
  //printf("Width %d\n", params.width);
  //printf("LEN %d\n", len);

}

void D_analizator(t_argc params, va_list ap)
{
  long int d;
  int len;
  int spaces;
  int zeros;

  zeros = 0;
  check_stars(&params, ap);
  d = va_arg(ap, long int);
  ft_putnbr(d);
  if (params.left)
    ft_putstr(params.left);
}

void o_analizator(t_argc params, va_list ap)
{
  unsigned int d;
  int len;
  int spaces;
  int zeros;

  check_stars(&params, ap);
  d = va_arg(ap, unsigned int);
  print_hex_o(d);
  if (params.left)
    ft_putstr(params.left);
}

void O_analizator(t_argc params, va_list ap)
{
  int len;
  int spaces;
  int zeros;
  check_stars(&params, ap);
}

void u_analizator(t_argc params, va_list ap)
{
  int d;
  int len;
  int spaces;
  int zeros;

  check_stars(&params, ap);
  d = va_arg(ap, int);
  ft_putnbr(d);
  if (params.left)
    ft_putstr(params.left);
}

void U_analizator(t_argc params, va_list ap)
{
  unsigned long d;
  int len;
  int spaces;
  int zeros;

  check_stars(&params, ap);
  d = va_arg(ap, unsigned long);
  ft_putnbr(d);
  if (params.left)
    ft_putstr(params.left);
}

void x_analizator(t_argc params, va_list ap)
{
  unsigned int d;
  int len;
  int spaces;
  int zeros;

  check_stars(&params, ap);
  d = va_arg(ap, unsigned int);
  print_hex_x(d);
  if (params.left)
    ft_putstr(params.left);
}

void X_analizator(t_argc params, va_list ap)
{
  unsigned int d;
  int len;
  int spaces;
  int zeros;

  check_stars(&params, ap);
  d = va_arg(ap, unsigned int);
  print_hex_X(d);
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
    if (params.width > 1)
    {
      spaces = params.width - 1;
      while (spaces--)
        write(1, " ", 1);
    }
    write(1, &c, 1);
  }
  if (params.left)
    ft_putstr(params.left);
}

void C_analizator(t_argc params, va_list ap)
{
  int len;
  int spaces;
  int zeros;
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
    if (params.width > 1)
    {
      spaces = params.width - 1;
      while (spaces--)
        write(1, " ", 1);
    }
    write(1, &C, 1);
  }
  if (params.left)
    ft_putstr(params.left);
}
