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
  int i;

  i = 0;
  if ((*params).width == '*')
  {
    (*params).width = va_arg(ap, int);
    if ((*params).width < 0)
    {
      (*params).width = (*params).width * -1;
      if (!if_flag((*params).flag, '-', FLAG_LIMIT))
        {
          while ((*params).flag[i] != 0)
            i++;
          (*params).flag[i] = '-';
        }
    }
  }
  i = 0;
  if ((*params).precision == '*')
  {
    (*params).precision = va_arg(ap, int);
  }
}

void print_int_depend_length(intmax_t *d, char *length, t_argc *params)
{
  /*if ((*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'u' || (*params).specifier == 'U'
  || (*params).specifier == 'x' || (*params).specifier == 'X')
    *d = (uintmax_t)*d;*/
  /*if (*d >= -9223372036854775807 && *d <= 9223372036854775807)
  {
    printf("ok\n");
    *d = (unsigned long long)*d;
  }*/
  if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'd' || (*params).specifier == 'i'))
    *d = (signed char)*d;
  else if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'u' ||
    (*params).specifier == 'o' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned char)*d;
  else if ((ft_strcmp(length, "ll") == 0) && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (long long)*d;
  else if ((ft_strcmp(length, "ll") == 0) && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned long long)*d;
  else if ((length[0] == 'h') && ((*params).specifier == 'd' || (*params).specifier == 'i'))
    *d = (short)*d;
  else if ((length[0] == 'h') && ((*params).specifier == 'u' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned short)*d;
  else if ((length[0] == 'l') && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (long)*d;
  else if ((length[0] == 'l') && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned long)*d;
  else if ((length[0] == 'z') && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (ssize_t)*d;
  else if ((length[0] == 'z') && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (size_t)*d;
  else if (length[0] == 'j')
  {
    if ((*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'u' || (*params).specifier == 'U'
    || (*params).specifier == 'x' || (*params).specifier == 'X')
      *d = (uintmax_t)*d;
  }
  else
  {
    if ((*params).specifier == 'O' || (*params).specifier == 'U')
      *d = (unsigned long)*d;
    else if ((*params).specifier == 'D')
      *d = (long)*d;
    else if ((*params).specifier == 'd' || (*params).specifier == 'i')
      *d = (int)*d;
    else
    {
      if ((*params).specifier != 'p')
        *d = (unsigned int)*d;
    }
  }
}

void print_uint_depend_length(uintmax_t *d, char *length, t_argc *params)
{
  /*if ((*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'u' || (*params).specifier == 'U'
  || (*params).specifier == 'x' || (*params).specifier == 'X')
    *d = (uintmax_t)*d;*/
  if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (signed char)*d;
  else if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'u' ||
  (*params).specifier == 'o' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned char)*d;
  else if ((ft_strcmp(length, "ll") == 0) && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (long long)*d;
  else if ((ft_strcmp(length, "ll") == 0) && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned long long)*d;
  else if ((length[0] == 'h') && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (short)*d;
  else if ((length[0] == 'h') && ((*params).specifier == 'u' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned short)*d;
  else if ((length[0] == 'l') && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (long)*d;
  else if ((length[0] == 'l') && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned long)*d;
  else if ((length[0] == 'z') && ((*params).specifier == 'd' || (*params).specifier == 'i' || (*params).specifier == 'D'))
    *d = (ssize_t)*d;
  else if ((length[0] == 'z') && ((*params).specifier == 'u' || (*params).specifier == 'U' ||
  (*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (size_t)*d;
  else if (length[0] == 'j')
  {
    if ((*params).specifier == 'o' || (*params).specifier == 'O' || (*params).specifier == 'u' || (*params).specifier == 'U'
    || (*params).specifier == 'x' || (*params).specifier == 'X')
      *d = (uintmax_t)*d;
  }
  else
  {
    if ((*params).specifier == 'O' || (*params).specifier == 'U')
      *d = (unsigned long)*d;
    else if ((*params).specifier == 'D')
      *d = (long)*d;
    else if ((*params).specifier == 'd' || (*params).specifier == 'i')
      *d = (int)*d;
    else
    {
      if ((*params).specifier != 'p')
        *d = (unsigned int)*d;
    }
  }
}

void print_params_left(intmax_t d, t_argc *params, int zeros, int spaces)
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
  if (((*params).specifier == 'o' || (*params).specifier == 'O') && if_flag((*params).flag, '#', FLAG_LIMIT) &&
   (d != 0 || (*params).precision != -1))
    write(1, "0", 1);
  if (d != 0)
  {
    if (d >= -9223372036854775807 && d <= 9223372036854775807)
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

void print_params_right(intmax_t d, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && d >= 0 /*&&
    !if_flag((*params).flag, '0', FLAG_LIMIT)*/ && !if_flag((*params).flag, '+', FLAG_LIMIT)
  && (*params).specifier != 'u' && (*params).specifier != 'U' &&
  (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
    if (if_flag((*params).flag, '0', FLAG_LIMIT))
      zeros -= 1;
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
  if (((*params).specifier == 'o' || (*params).specifier == 'O') && if_flag((*params).flag, '#', FLAG_LIMIT) &&
   (d != 0 || (*params).precision != -1))
    write(1, "0", 1);
  //printf("DDD %jud\n", d);
  if (d != 0)
  {
    if (d >= -9223372036854775807 && d <= 9223372036854775807)
      ft_put_long_nbr(d);
    else
      ft_put_uns_long_nbr(d);
  }
  else
    if ((*params).precision != 0)
      write(1, "0", 1);
}

void s_analizator(t_argc *params, va_list ap)
{
  char *s;
  long long len;
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
  else if ((*params).precision == 0)
    len = 0;
  (*params).res += len;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    if ((*params).precision != 0)
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
    if ((*params).precision != 0)
      write(1, s, len);
  }
  if ((*params).left)
  {
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
  }
}

void S_analizator(t_argc *params, va_list ap)
{
  int j;
  long long len;
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
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
  }
}

void d_analizator(t_argc *params, va_list ap)
{
  intmax_t d;
  intmax_t tmp;
  intmax_t len;
  int spaces;
  int zeros;
  zeros = 0;
  spaces = 0;
  len = 1;
  //printf("FLAG %c %c %c %c %c\n", (char)params.flag[0], (char)params.flag[1],
   // (char)params.flag[2], (char)params.flag[3], (char)params.flag[4]);
  //printf("WIDTH %d\n", params.width);
  //printf("PRECISION %d\n", params.precision);
 // printf("LENGTH %s\n", params.length);
 // printf("SPECIFIER %c\n", params.specifier);
 // printf("LEFT %s\n", params.left);
  check_stars(params, ap);
  d = va_arg(ap, intmax_t);
  //printf("DDD %jud\n", d);
  print_int_depend_length(&d, (*params).length, params);
  //printf("DDD %jud\n", d);
  tmp = d;
  if (d < -9223372036854775807 || d > 9223372036854775807)
    len = 20;
  else
  {
    if (d < 0)
    {
      len = 2;
      tmp = tmp * -1;
    }
  //printf("DDD %lld\n", d);
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
    if (d != 0)
    {
      while (tmp > 9)
      {
        tmp = tmp / 10;
        len++;
      }
    //len = ft_strlen(ft_itoa(d));
    //printf("DDD %d\n", len);
    }
    else
    {
      if ((*params).precision != 0)
        len = 1;
      else
        len = 0;
    }
}
  (*params).res += len;
  if ((*params).precision > 0)
    zeros = (*params).precision - len;
  if (zeros <= 0 && if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '-', FLAG_LIMIT))
    zeros = (*params).width - len;
  if (zeros > 0 && (*params).width > 1)
    spaces = (*params).width - len - zeros;
  if (zeros <= 0 && (*params).width > 1)
    spaces = (*params).width - len;
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
    print_params_left(d, params, zeros, spaces);
  else
    print_params_right(d, params, zeros, spaces);
  if ((*params).left)
  {
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
  }

  //printf("Prec %d\n", params.precision);
  //printf("Width %d\n", params.width);
  //printf("LEN %d\n", len);

}

void o_analizator(t_argc *params, va_list ap)
{
  intmax_t d;
  intmax_t tmp = 0;
  long long len;
  int spaces;
  int zeros;

  len = 1;
  spaces = 0;
  zeros = 0;
  check_stars(params, ap);
  d = va_arg(ap, intmax_t);
  //printf("DDD %jd\n", d);
  print_int_depend_length(&d, (*params).length, params);
  //printf("DDD %jd\n", d);
  if (d != 9223372036854775807)
    d = print_oct(d, 8);
  //printf("DDD %jd\n", d);

  tmp = d;
  if (d < 0)
  {
    len = 2;
    tmp = tmp * -1;
  }
  //printf("DDD %lld\n", d);
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (d != 0)
  {
    if (d == 9223372036854775807)
      len = 21;
    else
      while (tmp > 9)
      {
        tmp = tmp / 10;
        len++;
      }
    //len = ft_strlen(ft_itoa(d));
    //printf("DDD %d\n", len);
  }
  else
  {
    if ((*params).precision != 0)
      len = 1;
    else
      len = 0;
  }

  //printf("DDD %jd\n", len);
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
    if (d != 0 || (*params).precision != -1)
      (*params).res += 1;
  }
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (d == 9223372036854775807)
  {
    if (if_flag((*params).flag, '-', FLAG_LIMIT))
      long_print_params_left(d, params, zeros, spaces);
    else
      long_print_params_right(d, params, zeros, spaces);
  }
  else
  {
    if (if_flag((*params).flag, '-', FLAG_LIMIT))
      print_params_left(d, params, zeros, spaces);
    else
      print_params_right(d, params, zeros, spaces);
  }
  if ((*params).left)
  {
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
  }
}

void u_analizator(t_argc *params, va_list ap)
{
  uintmax_t d;
  uintmax_t tmp;
  uintmax_t len;
  int spaces;
  int zeros;
  zeros = 0;
  spaces = 0;
  len = 1;
  tmp = 0;
  //printf("FLAG %c %c %c %c %c\n", (char)params.flag[0], (char)params.flag[1],
   // (char)params.flag[2], (char)params.flag[3], (char)params.flag[4]);
  //printf("WIDTH %d\n", params.width);
  //printf("PRECISION %d\n", params.precision);
 // printf("LENGTH %s\n", params.length);
 // printf("SPECIFIER %c\n", params.specifier);
 // printf("LEFT %s\n", params.left);
  check_stars(params, ap);
  d = va_arg(ap, uintmax_t);
  print_uint_depend_length(&d, (*params).length, params);
  tmp = d;
  //printf("DDD %lld\n", d);
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
  if (d > 0)
  {
    /*if (d == 18446744073709551615)
      len = 20;
    else*/
      while (tmp > 9)
      {
        tmp = tmp / 10;
        len++;
      }
    //len = ft_strlen(ft_itoa(d));
    //printf("DDD %d\n", len);
  }
  else
  {
    if ((*params).precision != 0)
      len = 1;
    else
      len = 0;
  }
  //printf("FLAG %d% d\n", 12345, if_flag(params.flag, '-', FLAG_LIMIT));
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
    long_print_params_left(d, params, zeros, spaces);
  else
    long_print_params_right(d, params, zeros, spaces);
  if ((*params).left)
  {
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
  }
}

void x_analizator(t_argc *params, va_list ap)
{
  intmax_t d;
  intmax_t tmp;
  int len;
  int spaces;
  int zeros;
  char *s;
  s = NULL;
  tmp = 0;
  len = 0;
  spaces = 0;
  zeros = 0;
  check_stars(params, ap);
  d = va_arg(ap, intmax_t);
  //printf("DDD1 %d\n", d);
  print_int_depend_length(&d, (*params).length, params);
  //printf("DDD2 %d\n", d);
  tmp = d;
  s = print_hex(d, *params, 16);
  //printf("%s\n", s);
  if (d != 0)
   {
     len = ft_strlen(s);
   }
  /*  while (tmp >= 16)
    {
      tmp = tmp / 16;
      len++;
    }*/
  if (d == 0)
  {
    if ((*params).precision != 0)
      len = 1;
  }
/*  if (d < 0)
    while (tmp <= -16)
    {
      tmp = tmp / 16;
      len++;
    }*/
  //printf("LEN %d\n", len);
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
      ft_putstr(s);
      //print_hex(d, *params, 16);
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
      ft_putstr(s);
      //print_hex(d, *params, 16);
    else
      if ((*params).precision != 0)
        write(1, "0", 1);
  }
  if ((*params).left)
  {
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
    //ft_putstr((*params).left);
  }
  if (s)
    free(s);
}

void c_analizator(t_argc *params, va_list ap)
{
  unsigned char c;
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
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
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
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
  }
}
