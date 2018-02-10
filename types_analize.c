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

void print_signed_int_depend_length(intmax_t *d, char *length, t_argc *params)
{
  if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (signed char)*d;
  else if ((ft_strcmp(length, "ll") == 0) && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (long long)*d;
  else if ((length[0] == 'h') && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (short)*d;
  else if ((length[0] == 'l') && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (long)*d;
  else if (length[0] == 'z')
    *d = (size_t)*d;
  else
    *d = (int)*d;
}

void print_unsigned_int_depend_length(uintmax_t *d, char *length, t_argc *params)
{
  if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned char)*d;
  else if ((ft_strcmp(length, "ll") == 0) && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned long  long)*d;
  else if ((length[0] == 'h') && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned short)*d;
  else if ((length[0] == 'l') && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned long)*d;
  else if (length[0] == 'z')
    *d = (size_t)*d;
  else
    *d = (unsigned int)*d;
}

void print_int_params_left(intmax_t d, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && d >= 0 && (*params).specifier
    != 'u' && (*params).specifier != 'U' && !if_flag((*params).flag, '+', FLAG_LIMIT)
    && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
  }
  if (d >= 0 && if_flag((*params).flag, '+', FLAG_LIMIT) && (*params).specifier != 'o' && (*params).specifier != 'O')
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

void print_int_params_right(intmax_t d, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && d >= 0 &&
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
      && (*params).specifier != 'o' && (*params).specifier != 'O')
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
      //printf("%d\n", d);
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
  if (d != 0)
    ft_putnbr(d);
  else
    if ((*params).precision != 0)
      write(1, "0", 1);
}

void s_analizator(t_argc *params, va_list ap)
{
  char *s;
  int len;
  int spaces;

  spaces = 0;
  len = 0;
  s = NULL;
  check_stars(params, ap);
  s = va_arg(ap, char *);
  if (s == NULL)
    s = "(null)";
  len = ft_strlen(s);
  if ((*params).precision > 0 && (*params).precision < len)
    len = (*params).precision;
  (*params).res += len;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    write(1, s, len);
    if ((*params).width > len)
    {
      spaces = (*params).width - len;
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
  }
  else
  {
    if ((*params).width > len && !if_flag((*params).flag, '0', FLAG_LIMIT))
    {
      spaces = (*params).width - len;
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
    else if ((*params).width > len && if_flag((*params).flag, '0', FLAG_LIMIT))
    {
      spaces = (*params).width - len;
      (*params).res += spaces;
      while (spaces--)
        write(1, "0", 1);
    }
    write(1, s, len);
  }
  if ((*params).left)
  {
    (*params).res += ft_strlen((*params).left);
    ft_putstr((*params).left);
  }
}

void S_analizator(t_argc *params, va_list ap)
{
  int j;
  int len;
  int spaces;
  wchar_t *S;

  j = 0;
  spaces = 0;
  len = 0;
  S = NULL;
  check_stars(params, ap);
  S = va_arg(ap, wchar_t *);
  while(S[len])
    len++;
  if ((*params).precision > 0 && (*params).precision < len)
    len = (*params).precision;
  (*params).res += len;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    while(S[j])
    {
      write(1, &S[j], 1);
      j += 1;
    }
    if ((*params).width > len)
    {
      spaces = (*params).width - len;
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
  }
  else
  {
    if ((*params).width > len && !if_flag((*params).flag, '0', FLAG_LIMIT))
    {
      spaces = (*params).width - len;
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
    else if ((*params).width > len && if_flag((*params).flag, '0', FLAG_LIMIT))
    {
      spaces = (*params).width - len;
      (*params).res += spaces;
      while (spaces--)
        write(1, "0", 1);
    }
    while(S[j])
    {
      write(1, &S[j], 1);
      j += 1;
    }
  }
  if ((*params).left)
  {
    (*params).res += ft_strlen((*params).left);
    ft_putstr((*params).left);
  }
}

void d_analizator(t_argc *params, va_list ap)
{
  intmax_t d;
  int len;
  int spaces;
  int zeros;
  zeros = 0;
  spaces = 0;
  len = 0;
  //printf("FLAG %c %c %c %c %c\n", (char)params.flag[0], (char)params.flag[1],
   // (char)params.flag[2], (char)params.flag[3], (char)params.flag[4]);
  //printf("WIDTH %d\n", params.width);
  //printf("PRECISION %d\n", params.precision);
 // printf("LENGTH %s\n", params.length);
 // printf("SPECIFIER %c\n", params.specifier);
 // printf("LEFT %s\n", params.left);
  check_stars(params, ap);
  d = va_arg(ap, intmax_t);
  print_signed_int_depend_length(&d, (*params).length, params);
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (d != 0)
    len = ft_strlen(ft_itoa(d));
  else
    if ((*params).precision != 0)
      len = 1;
  (*params).res += len;
  //printf("LLLEN %d\n", (*params).res);
  if ((*params).precision > 0)
    zeros = (*params).precision - len;
  else if (if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '-', FLAG_LIMIT))
    zeros = (*params).width - len;
  if (zeros > 0 && (*params).width > 1)
    spaces = (*params).width - len - zeros;
  if (zeros <= 0 && (*params).width > 1)
    spaces = (*params).width - len;
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
    print_int_params_left(d, params, zeros, spaces);
  else
    print_int_params_right(d, params, zeros, spaces);

  if ((*params).left)
  {
    (*params).res += ft_strlen((*params).left);
    ft_putstr((*params).left);
  }

  //printf("Prec %d\n", params.precision);
  //printf("Width %d\n", params.width);
  //printf("LEN %d\n", len);

}

void o_analizator(t_argc *params, va_list ap)
{
  uintmax_t d;
  int len;
  int spaces;
  int zeros;

  len = 0;
  spaces = 0;
  zeros = 0;

  check_stars(params, ap);
  d = va_arg(ap, uintmax_t);
  d = print_oct(d, 8);
  print_unsigned_int_depend_length(&d, (*params).length, params);
  if (d != 0)
    len = ft_strlen(ft_itoa(d));
  else
    if ((*params).precision != 0)
      len = 1;
  (*params).res += len;
  if ((*params).precision > 0)
    zeros = (*params).precision - len;
  else if (if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '-', FLAG_LIMIT))
    zeros = (*params).width - len;
  if (zeros > 0 && (*params).width > 1)
    spaces = (*params).width - len - zeros;
  if (zeros <= 0 && (*params).width > 1)
    spaces = (*params).width - len;
  if (if_flag((*params).flag, '#', FLAG_LIMIT))
  {
    zeros--;
    spaces--;
    (*params).res += 1;
  }
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
    print_uint_params_left(d, params, zeros, spaces);
  else
    print_uint_params_right(d, params, zeros, spaces);
  if ((*params).left)
  {
    (*params).res += ft_strlen((*params).left);
    ft_putstr((*params).left);
  }
}

void u_analizator(t_argc *params, va_list ap)
{
  uintmax_t d;
  int len;
  int spaces;
  int zeros;
  zeros = 0;
  spaces = 0;
  len = 0;
  //printf("FLAG %c %c %c %c %c\n", (char)params.flag[0], (char)params.flag[1],
   // (char)params.flag[2], (char)params.flag[3], (char)params.flag[4]);
  //printf("WIDTH %d\n", params.width);
  //printf("PRECISION %d\n", params.precision);
 // printf("LENGTH %s\n", params.length);
 // printf("SPECIFIER %c\n", params.specifier);
 // printf("LEFT %s\n", params.left);
  check_stars(params, ap);
  d = va_arg(ap, uintmax_t);
  print_unsigned_int_depend_length(&d, (*params).length, params);
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (d != 0)
    len = ft_strlen(ft_itoa(d));
  else
    if ((*params).precision != 0)
      len = 1;
  (*params).res += len;
  //printf("LLLEN %d\n", (*params).res);
  if ((*params).precision > 0)
    zeros = (*params).precision - len;
  else if (if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '-', FLAG_LIMIT))
    zeros = (*params).width - len;
  if (zeros > 0 && (*params).width > 1)
    spaces = (*params).width - len - zeros;
  if (zeros <= 0 && (*params).width > 1)
    spaces = (*params).width - len;
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
    print_uint_params_left(d, params, zeros, spaces);
  else
    print_uint_params_right(d, params, zeros, spaces);

  if ((*params).left)
  {
    (*params).res += ft_strlen((*params).left);
    ft_putstr((*params).left);
  }
}

void x_analizator(t_argc *params, va_list ap)
{
  uintmax_t d;
  int tmp;
  int len;
  int spaces;
  int zeros;
  tmp = 0;
  len = 1;
  spaces = 0;
  zeros = 0;
  check_stars(params, ap);
  d = va_arg(ap, uintmax_t);
  print_unsigned_int_depend_length(&d, (*params).length, params);
  tmp = d;
  if (d != 0)
    while (tmp >= 16)
    {
      tmp = tmp / 16;
      len++;
    }
  else
    if ((*params).precision != 0)
      len = 1;
    else
      len = 0;
  (*params).res += len;
  if ((*params).precision > 0)
    zeros = (*params).precision - len;
  else if (if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '-', FLAG_LIMIT))
    zeros = (*params).width - len;
  if (zeros > 0 && (*params).width > 1)
    spaces = (*params).width - len - zeros;
  if (zeros <= 0 && (*params).width > 1)
    spaces = (*params).width - len;
  if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0) || (*params).specifier == 'p')
  {
    spaces -= 2;
    zeros -= 2;
  }
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0) || (*params).specifier == 'p')
    {
      //zeros--;
      (*params).res += 2;
      write(1, "0", 1);
      if ((*params).specifier == 'x' || (*params).specifier == 'p')
        write(1, "x", 1);
      else
        write(1, "X", 1);
    }
    if (zeros > 0)
    {
      (*params).res += zeros;
      while (zeros--)
        write(1, "0", 1);
    }
    if (d != 0)
      print_hex(d, *params, 16);
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
  else
  {
    if (spaces > 0 && zeros > 0)
    {
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
    if (spaces > 0 && zeros <= 0)
    {
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
    if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0) || (*params).specifier == 'p')
    {
      //zeros--;
      (*params).res += 2;
      write(1, "0", 1);
      if ((*params).specifier == 'x' || (*params).specifier == 'p')
        write(1, "x", 1);
      else
        write(1, "X", 1);
    }
    if (zeros > 0)
    {
      (*params).res += zeros;
      while (zeros--)
        write(1, "0", 1);
    }
    if (d != 0)
      print_hex(d, *params, 16);
    else
      if ((*params).precision != 0)
        write(1, "0", 1);
  }
  if ((*params).left)
  {
    (*params).res += ft_strlen((*params).left);
    ft_putstr((*params).left);
  }
}

void c_analizator(t_argc *params, va_list ap)
{
  char c;
  int spaces;

  spaces = 0;
  check_stars(params, ap);
  if ((*params).specifier != '%')
    c = va_arg(ap, int);
  else
    c = (*params).specifier;
  //printf("CCC %c\n", c);
  (*params).res += 1;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    write(1, &c, 1);
    if ((*params).width > 1)
    {
      spaces = (*params).width - 1;
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
  }
  else
   {
     if ((*params).width > 1 && !if_flag((*params).flag, '0', FLAG_LIMIT))
     {
       spaces = (*params).width - 1;
       (*params).res += spaces;
       while (spaces--)
         write(1, " ", 1);
     }
     else if ((*params).width > 1 && if_flag((*params).flag, '0', FLAG_LIMIT))
     {
       spaces = (*params).width - 1;
       (*params).res += spaces;
       while (spaces--)
         write(1, "0", 1);
     }
    write(1, &c, 1);
  }
  if ((*params).left)
  {
    (*params).res += ft_strlen((*params).left);
    ft_putstr((*params).left);
  }
}

void C_analizator(t_argc *params, va_list ap)
{
  //int len;
  int spaces;
  //int zeros;
  wchar_t C;
  spaces = 0;

  check_stars(params, ap);
  C = va_arg(ap, wchar_t);
  (*params).res += 1;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    write(1, &C, 1);
    if ((*params).width > 1)
    {
      spaces = (*params).width - 1;
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
  }
  else
  {
    if ((*params).width > 1 && !if_flag((*params).flag, '0', FLAG_LIMIT))
    {
      spaces = (*params).width - 1;
      (*params).res += spaces;
      while (spaces--)
        write(1, " ", 1);
    }
    else if ((*params).width > 1 && if_flag((*params).flag, '0', FLAG_LIMIT))
    {
      spaces = (*params).width - 1;
      (*params).res += spaces;
      while (spaces--)
        write(1, "0", 1);
    }
    write(1, &C, 1);
  }
  if ((*params).left)
  {
    (*params).res += ft_strlen((*params).left);
    ft_putstr((*params).left);
  }
}
