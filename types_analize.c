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

void print_left(t_argc *params)
{
  if ((*params).left)
  {
    (*params).res += (*params).left_len;
    write(1, (*params).left, (*params).left_len);
  }
}

void check_stars(t_argc *params, va_list ap)
{
  int i;

  i = 0;
  if ((*params).star_width == '*')
    (*params).star_width = va_arg(ap, int);
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
    (*params).precision = va_arg(ap, int);
}

void ox_depend_length(intmax_t *d, char *length, t_argc *params)
{
  if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'o' ||
  (*params).specifier == 'x' || (*params).specifier == 'X'))
    *d = (unsigned char)*d;
  else if (ft_strcmp(length, "ll") == 0)
    *d = (unsigned long long)*d;
  else if (length[0] == 'h')
    *d = (unsigned short)*d;
  else if (length[0] == 'l')
    *d = (unsigned long)*d;
  else if (length[0] == 'z')
    *d = (size_t)*d;
  else if (length[0] == 'j')
    *d = (uintmax_t)*d;
  else
  {
    if ((*params).specifier == 'O')
      *d = (unsigned long)*d;
    else
    {
      if ((*params).specifier != 'p')
        *d = (unsigned int)*d;
    }
  }
}

void int_depend_length(intmax_t *d, char *length, t_argc *params)
{
  if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'd' || (*params).specifier == 'i'))
    *d = (signed char)*d;
  else if (ft_strcmp(length, "ll") == 0)
    *d = (long long)*d;
  else if ((length[0] == 'h') && ((*params).specifier == 'd' || (*params).specifier == 'i'))
    *d = (short)*d;
  else if (length[0] == 'l')
    *d = (long)*d;
  else if (length[0] == 'z')
    *d = (ssize_t)*d;
  else if (length[0] != 'j')
  {
    if ((*params).specifier == 'D')
      *d = (long)*d;
    else
      *d = (int)*d;
  }
}

void u_depend_length(uintmax_t *d, char *length, t_argc *params)
{
  if ((ft_strcmp(length, "hh") == 0) && (*params).specifier == 'u')
    *d = (unsigned char)*d;
  else if (ft_strcmp(length, "ll") == 0)
    *d = (unsigned long long)*d;
  else if (length[0] == 'h' && (*params).specifier == 'u')
    *d = (unsigned short)*d;
  else if (length[0] == 'l')
    *d = (unsigned long)*d;
  else if (length[0] == 'z')
    *d = (size_t)*d;
  else if (length[0] == 'j')
    *d = (uintmax_t)*d;
  else
  {
    if ((*params).specifier == 'U')
      *d = (unsigned long)*d;
    else
      *d = (unsigned int)*d;
  }
}

void print_params_left(char *s, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && (*params).sign != '-' && (*params).specifier
    != 'u' && (*params).specifier != 'U' && !if_flag((*params).flag, '+', FLAG_LIMIT)
    && (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
  }
  if ((*params).sign != '-' && if_flag((*params).flag, '+', FLAG_LIMIT) &&
  (*params).specifier != 'o' && (*params).specifier != 'O'
  && (*params).specifier != 'u' && (*params).specifier != 'U')
  {
    (*params).res += 1;
    spaces -= 1;
    write(1, "+", 1);
  }
  if ((*params).sign == '-' && zeros > 0)
  {
      (*params).sign = 0;
      spaces--;
      write(1, "-", 1);
      zeros += 1;
  }
  if (zeros > 0)
  {
    (*params).res += zeros;
    while (zeros--)
      write(1, "0", 1);
  }
  if (((*params).specifier == 'o' || (*params).specifier == 'O') &&
  if_flag((*params).flag, '#', FLAG_LIMIT) &&
   (s[0] != '0' || (*params).precision != -1))
    write(1, "0", 1);
  if (s[0] != '0')
  {
    if ((*params).sign == '-' && s[0] != '-')
      write(1, "-", 1);
    ft_putstr(s);
    if (s[0] == '-')
      (*params).res--;
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

void print_params_right(char *s, t_argc *params, int zeros, int spaces)
{
  if (if_flag((*params).flag, ' ', FLAG_LIMIT) && (*params).sign != '-'
  && !if_flag((*params).flag, '+', FLAG_LIMIT)
  && (*params).specifier != 'u' && (*params).specifier != 'U' &&
  (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    (*params).res += 1;
    write(1, " ", 1);
    spaces -= 1;
    if (if_flag((*params).flag, '0', FLAG_LIMIT) && (*params).width > 0 && (*params).precision <= 0)
      zeros -= 1;
  }
  if ((*params).sign != '-' && if_flag((*params).flag, '+', FLAG_LIMIT) &&
  (*params).specifier != 'o' && (*params).specifier != 'O')
  {
    spaces -= 1;
    if ((*params).precision <= 0)
      zeros -= 1;
  }
  if (spaces > 0 && zeros > 0)
  {
    if ((*params).sign == '-' && zeros > 0)
      spaces--;
    (*params).res += spaces;
    while (spaces--)
      write(1, " ", 1);
  }
  if (spaces > 0 && zeros <= 0)
  {
    if ((*params).sign == '-' && zeros > 0)
      spaces--;
    (*params).res += spaces;
    while (spaces--)
      write(1, " ", 1);
  }
  if ((*params).sign == '-' && zeros > 0)
  {
      write(1, "-", 1);
      (*params).sign = 1;
      if ((*params).precision > 0 && !if_flag((*params).flag, '0', FLAG_LIMIT))
        zeros += 1;
  }
  if ((*params).sign != '-' && (*params).sign != 1 && if_flag((*params).flag, '+', FLAG_LIMIT)
      && (*params).specifier != 'o' && (*params).specifier != 'O'
      && (*params).specifier != 'u' && (*params).specifier != 'U')
  {
    (*params).res += 1;
    write(1, "+", 1);
  }
  if (zeros > 0)
  {
    (*params).res += zeros;
    while (zeros--)
      write(1, "0", 1);
  }
  if (((*params).specifier == 'o' || (*params).specifier == 'O') &&
   if_flag((*params).flag, '#', FLAG_LIMIT) &&
   (s[0] != '0' || (*params).precision != -1))
    write(1, "0", 1);
  if (s[0] != '0')
  {
    if ((*params).sign == '-' && s[0] != '-')
      write(1, "-", 1);
    ft_putstr(s);
    if (s[0] == '-')
      (*params).res--;
  }
  else
    if ((*params).precision != 0)
      write(1, "0", 1);
}

void	elems_init(t_forprint *elems)
{
	(*elems).len = 0;
	(*elems).spaces = 0;
	(*elems).zeros = 0;
	(*elems).s = NULL;
  (*elems).S = NULL;
}

void count_spaces_and_zeros(t_forprint *elems, t_argc *params)
{
  if ((*params).specifier == 's')
  {
    if (if_flag((*params).flag, '0', FLAG_LIMIT))
      (*elems).spaces = (*params).width - (*elems).len;
    else
      (*elems).spaces = (*params).width - 1;
  }
  if ((*params).specifier == 'S')
  {
    if (if_flag((*params).flag, '0', FLAG_LIMIT))
      (*elems).zeros = (*params).width - (*elems).len;
    (*elems).spaces = (*params).width - (*elems).len - (*elems).zeros;
  }
}

void s_analizator(t_argc *params, va_list ap)
{
  t_forprint elems;

  elems_init(&elems);
  check_stars(params, ap);
  if ((*params).specifier == 's' || (*params).specifier == 'S')
    elems.s = va_arg(ap, char *);
  else
    elems.s = (*params).reserve;
  if (elems.s == NULL)
    elems.s = "(null)";
  elems.len = ft_strlen(elems.s);
  if ((*params).precision > 0 && (*params).precision < elems.len)
    elems.len = (*params).precision;
  else if ((*params).precision == 0)
    elems.len = 0;
  (*params).res += elems.len;
  //count_spaces_and_zeros(&elems, params);
  if ((*params).specifier == 's' || (*params).specifier == 'S' || if_flag((*params).flag, '0', FLAG_LIMIT))
    elems.spaces = (*params).width - elems.len;
  else
    elems.spaces = (*params).width - 1;
  if (elems.spaces > 0)
    (*params).res += elems.spaces;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    if ((*params).precision != 0)
      write(1, elems.s, elems.len);
    if ((*params).width > elems.len)
      while (elems.spaces--)
        write(1, " ", 1);
  }
  else
  {
    if ((*params).width > elems.len && !if_flag((*params).flag, '0', FLAG_LIMIT))
      while (elems.spaces--)
        write(1, " ", 1);
    else if ((*params).width > elems.len && if_flag((*params).flag, '0', FLAG_LIMIT))
      while (elems.spaces--)
        write(1, "0", 1);
    if ((*params).precision != 0)
      write(1, elems.s, elems.len);
  }
  print_left(params);
}

void S_analizator(t_argc *params, va_list ap)
{
  int j;
  t_forprint elems;

  j = 0;
  elems_init(&elems);
  check_stars(params, ap);
  elems.S = va_arg(ap, wchar_t *);
  if (elems.S == NULL)
    elems.len = 6;
  else
    elems.len = ft_strlen_wide(elems.S);
  if ((*params).precision >= 0)
    elems.len = (*params).precision;
  (*params).res += elems.len;
  //count_spaces_and_zeros(&elems, params);
  if (if_flag((*params).flag, '0', FLAG_LIMIT))
    elems.zeros = (*params).width - elems.len;
  elems.spaces = (*params).width - elems.len - elems.zeros;
  if (elems.spaces > 0)
    (*params).res += elems.spaces;
  if (elems.zeros > 0)
    (*params).res += elems.zeros;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    if (elems.zeros > 0)
    {
      while (elems.zeros--)
        write(1, "0", 1);
    }
    if (elems.S == NULL)
      write(1, "(null)", 6);
    else
    {
      print_unicode(elems.S, elems.len, params);
    }
    if (elems.spaces > 0)
      while (elems.spaces--)
        write(1, " ", 1);
  }
  else
  {
    if (elems.spaces > 0)
      while (elems.spaces--)
        write(1, " ", 1);
    if (elems.zeros > 0)
    {
      while (elems.zeros--)
        write(1, "0", 1);
    }
    if (elems.S == NULL)
      write(1, "(null)", 6);
    else
    {
      print_unicode(elems.S, elems.len, params);
    }
  }
  print_left(params);
}

void d_analizator(t_argc *params, va_list ap)
{
  intmax_t d;
  t_forprint elems;

  elems_init(&elems);
  elems.len = 1;
  check_stars(params, ap);
  d = va_arg(ap, intmax_t);
  int_depend_length(&d, (*params).length, params);
  if (d < 0)
  {
    (*params).sign = '-';
    d = -1 * d;
  }
  elems.s = ft_itoa(d);
  if (d != 0)
  {
    elems.len = ft_strlen(elems.s);
    if ((*params).sign == '-')
      elems.len++;
  }
    else
    {
      if ((*params).precision != 0)
        elems.len = 1;
      else
        elems.len = 0;
    }
  (*params).res += elems.len;
  if ((*params).precision > 0)
    elems.zeros = (*params).precision - elems.len;
  if (elems.zeros <= 0 && if_flag((*params).flag, '0', FLAG_LIMIT)
    && !if_flag((*params).flag, '-', FLAG_LIMIT) && (*params).precision != 0)
    elems.zeros = (*params).width - elems.len;
  if (elems.zeros > 0 && (*params).width > 1)
    elems.spaces = (*params).width - elems.len - elems.zeros;
  if (elems.zeros <= 0 && (*params).width > 1)
    elems.spaces = (*params).width - elems.len;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
    print_params_left(elems.s, params, elems.zeros, elems.spaces);
  else
    print_params_right(elems.s, params, elems.zeros, elems.spaces);
  print_left(params);
  ft_strdel(&elems.s);
}

void o_analizator(t_argc *params, va_list ap)
{
  intmax_t d;
  t_forprint elems;

  elems_init(&elems);
  elems.len = 1;
  check_stars(params, ap);
  d = va_arg(ap, intmax_t);
  ox_depend_length(&d, (*params).length, params);
  elems.s = print_hex(d, *params, 8, 30);
  if (d != 0)
    elems.len = ft_strlen(elems.s);
  else
  {
    if ((*params).precision != 0)
      elems.len = 1;
    else
      elems.len = 0;
  }
  (*params).res += elems.len;
  if ((*params).precision > 0)
    elems.zeros = (*params).precision - elems.len;
  else if (if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '-', FLAG_LIMIT))
    elems.zeros = (*params).width - elems.len;
  if (elems.zeros > 0 && (*params).width > 1)
    elems.spaces = (*params).width - elems.len - elems.zeros;
  if (elems.zeros <= 0 && (*params).width > 1)
    elems.spaces = (*params).width - elems.len;
  if (if_flag((*params).flag, '#', FLAG_LIMIT))
  {
    elems.zeros--;
    if (d != 0 || (*params).precision != 0)
    {
      if ((*params).precision <= 0)
      elems.spaces--;
      if (d != 0 || (*params).precision > 0)
        (*params).res += 1;
    }
    else if (d == 0 && (*params).precision <= 0)
      (*params).res += 1;
  }
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
    print_params_left(elems.s, params, elems.zeros, elems.spaces);
  else
    print_params_right(elems.s, params, elems.zeros, elems.spaces);
  print_left(params);
  ft_strdel(&elems.s);
}

void u_analizator(t_argc *params, va_list ap)
{
  uintmax_t d;
  t_forprint elems;

  elems_init(&elems);
  elems.len = 1;
  check_stars(params, ap);
  d = va_arg(ap, uintmax_t);
  u_depend_length(&d, (*params).length, params);
  elems.s = ft_uns_itoa(d);
  if (d != 0)
    elems.len = ft_strlen(elems.s);
  else
  {
    if ((*params).precision != 0)
      elems.len = 1;
    else
      elems.len = 0;
  }
  (*params).res += elems.len;
  if ((*params).precision > 0)
    elems.zeros = (*params).precision - elems.len;
  else if (if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '-', FLAG_LIMIT))
    elems.zeros = (*params).width - elems.len;
  if (elems.zeros > 0 && (*params).width > 1)
    elems.spaces = (*params).width - elems.len - elems.zeros;
  if (elems.zeros <= 0 && (*params).width > 1)
    elems.spaces = (*params).width - elems.len;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
    print_params_left(elems.s, params, elems.zeros, elems.spaces);
  else
    print_params_right(elems.s, params, elems.zeros, elems.spaces);
  print_left(params);
}

void x_analizator(t_argc *params, va_list ap)
{
  intmax_t d;
  t_forprint elems;

  elems_init(&elems);
  check_stars(params, ap);
  d = va_arg(ap, intmax_t);
  ox_depend_length(&d, (*params).length, params);
  elems.s = print_hex(d, *params, 16, 16);
  if (d != 0)
     elems.len = ft_strlen(elems.s);
  if (d == 0 && (*params).precision != 0)
      elems.len = 1;
  (*params).res += elems.len;
  if ((*params).precision > 0)
    elems.zeros = (*params).precision - elems.len;
  else if (if_flag((*params).flag, '0', FLAG_LIMIT) && !if_flag((*params).flag, '-', FLAG_LIMIT))
    elems.zeros = (*params).width - elems.len;
  if (elems.zeros > 0 && (*params).width > 1)
    elems.spaces = (*params).width - elems.len - elems.zeros;
  if (elems.zeros <= 0 && (*params).width > 1)
    elems.spaces = (*params).width - elems.len;
  if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0) || (*params).specifier == 'p')
  {
    elems.spaces -= 2;
    if (if_flag((*params).flag, '0', FLAG_LIMIT))
      elems.zeros -= 2;
  }
  if (elems.zeros > 0)
    (*params).res += elems.zeros;
  if (elems.spaces > 0)
    (*params).res += elems.spaces;
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0) || (*params).specifier == 'p')
    {
      (*params).res += 2;
      write(1, "0", 1);
      if ((*params).specifier == 'x' || (*params).specifier == 'p')
        write(1, "x", 1);
      else
        write(1, "X", 1);
    }
    if (elems.zeros > 0)
      while (elems.zeros--)
        write(1, "0", 1);
    if (d != 0)
      ft_putstr(elems.s);
    else if ((*params).precision != 0)
      write(1, "0", 1);
    if (elems.spaces > 0)
      while (elems.spaces--)
        write(1, " ", 1);
  }
  else
  {
    if (elems.spaces > 0)
      while (elems.spaces--)
        write(1, " ", 1);
    if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0) || (*params).specifier == 'p')
    {
      (*params).res += 2;
      write(1, "0", 1);
      if ((*params).specifier == 'x' || (*params).specifier == 'p')
        write(1, "x", 1);
      else
        write(1, "X", 1);
    }
    if (elems.zeros > 0)
      while (elems.zeros--)
        write(1, "0", 1);
    if (d != 0)
      ft_putstr(elems.s);
    else if ((*params).precision != 0)
      write(1, "0", 1);
  }
  print_left(params);
  ft_strdel(&elems.s);
}

void c_analizator(t_argc *params, va_list ap)
{
  unsigned char c;
  t_forprint elems;

  elems_init(&elems);
  check_stars(params, ap);
  if ((*params).specifier == 'c')
    c = va_arg(ap, int);
  else
    c = (*params).specifier;
  (*params).res += 1;
  if ((*params).width > 1)
  {
    elems.spaces = (*params).width - 1;
    (*params).res += elems.spaces;
  }
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    write(1, &c, 1);
    if ((*params).width > 1)
      while (elems.spaces--)
        write(1, " ", 1);
  }
  else
   {
     if ((*params).width > 1 && !if_flag((*params).flag, '0', FLAG_LIMIT))
       while (elems.spaces--)
         write(1, " ", 1);
     else if ((*params).width > 1 && if_flag((*params).flag, '0', FLAG_LIMIT))
       while (elems.spaces--)
         write(1, "0", 1);
    write(1, &c, 1);
  }
  print_left(params);
}

void C_analizator(t_argc *params, va_list ap)
{
  t_forprint elems;
  wchar_t C;

  elems_init(&elems);
  check_stars(params, ap);
  C = va_arg(ap, wchar_t);
  if (C <= 127)
    elems.len = 1;
  else
    elems.len = ft_strlen_wide(&C);
  (*params).res += elems.len;
  if ((*params).width > elems.len)
  {
    elems.spaces = (*params).width - elems.len;
    (*params).res += elems.spaces;
  }
  if (if_flag((*params).flag, '-', FLAG_LIMIT))
  {
    print_unicode(&C, elems.len, params);
    if ((*params).width > elems.len)
      while (elems.spaces--)
        write(1, " ", 1);
  }
  else
  {
    if ((*params).width > elems.len && !if_flag((*params).flag, '0', FLAG_LIMIT))
      while (elems.spaces--)
        write(1, " ", 1);
    else if ((*params).width > elems.len && if_flag((*params).flag, '0', FLAG_LIMIT))
      while (elems.spaces--)
        write(1, "0", 1);
    print_unicode(&C, elems.len, params);
  }
  print_left(params);
}
