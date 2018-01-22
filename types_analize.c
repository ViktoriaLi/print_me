#include "ft_printf.h"
#include <stdio.h>

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

  check_stars(&params, ap);
  s = va_arg(ap, char *);

  write(1, s, ft_strlen(s));
  if (params.left)
    ft_putstr(params.left);
}

void S_analizator(t_argc params, va_list ap)
{
  int j;
  wchar_t *S;

  check_stars(&params, ap);
  S = va_arg(ap, wchar_t *);
  j = 0;
  while (S[j])
  {
    write(1, &S[j], 1);
    j += 1;
  }
  if (params.left)
    ft_putstr(params.left);
}

void p_analizator(t_argc params, va_list ap)
{
  check_stars(&params, ap);
}

void d_analizator(t_argc params, va_list ap)
{
  int d;
  int len;
  check_stars(&params, ap);
  d = va_arg(ap, int);
  len = 0;
  len = params.width - ft_strlen(ft_itoa(d));
  if (params.flag == '+')
    len = len - 1;
  printf("LEN1 %d\n", len);
  if (len > 0 && params.flag != '-')
  {
      write(1, " ", len);
  }
  if (params.flag == '+')
    write(1, &params.flag, 1);
  ft_putnbr(d);
  if (len > 0 && params.flag == '-')
  {
      write(1, " ", len);
  }
  if (params.left)
    ft_putstr(params.left);
  printf("WIDTH %d\n", params.width);
  printf("PRECISION %d\n", params.precision);
}

void D_analizator(t_argc params, va_list ap)
{
  check_stars(&params, ap);
}

void i_analizator(t_argc params, va_list ap)
{
  int d;

  check_stars(&params, ap);
  d = va_arg(ap, int);
  if (params.flag == '+')
    write(1, &params.flag, 1);
  ft_putnbr(d);
  if (params.left)
    ft_putstr(params.left);
}

void o_analizator(t_argc params, va_list ap)
{
  check_stars(&params, ap);
}

void O_analizator(t_argc params, va_list ap)
{
  check_stars(&params, ap);
}

void u_analizator(t_argc params, va_list ap)
{
  int d;

  check_stars(&params, ap);
  d = va_arg(ap, int);
  ft_putnbr(d);
  if (params.left)
    ft_putstr(params.left);
}

void U_analizator(t_argc params, va_list ap)
{
  check_stars(&params, ap);
}

void x_analizator(t_argc params, va_list ap)
{
  check_stars(&params, ap);
}

void X_analizator(t_argc params, va_list ap)
{
  check_stars(&params, ap);
}

void c_analizator(t_argc params, va_list ap)
{
  char c;

  check_stars(&params, ap);
  c = va_arg(ap, int);
  write(1, &c, 1);
  if (params.left)
    ft_putstr(params.left);
}

void C_analizator(t_argc params, va_list ap)
{
  wchar_t C;

  check_stars(&params, ap);
  C = va_arg(ap, wchar_t);
  write(1, &C, 1);
  if (params.left)
    ft_putstr(params.left);
}
