#include "ft_printf.h"
#include <stdio.h>

char *print_hex(uintmax_t nbr, t_argc params, unsigned int base, int count)
{
	static char *res;
	static int i;

	i = 0;
	res = NULL;
	res = (char *)malloc(count + 1);
	while (i < count)
		res[i++] = 0;
	i = 0;
	if (nbr >= base)
		print_hex(nbr / base, params, base, count);
	if ((nbr % base) < 10)
		res[i++] = (nbr % base) + 48;
	else if (params.specifier == 'x' || params.specifier == 'p')
		res[i++] = (nbr % base) - 10 + 97;
	else if (params.specifier == 'X')
		res[i++] = (nbr % base) - 10 + 65;
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
	else if (d != 0)
	  ft_put_uns_long_nbr(d);
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
	else if (d != 0)
	  ft_put_uns_long_nbr(d);
	else
	   if ((*params).precision != 0)
	     write(1, "0", 1);
}

void print_unicode(wchar_t *test, int len)
{
	//setlocale (LC_ALL, "");
	int i;
	int j;
	int bytes_count;
	int code;
	char res[4];
	unsigned int first[4];
	int shift;

	i = 0;
	j = 0;
	code = 0;
	bytes_count = 0;

	//wchar_t *test;
	//test = L"l䀥dⱢfdаd䋃fsf‣sd偤a";

	while (test[i] && i < len)
	{
		if (test[i] <= 127)
		{
			write(1, &test[i], 1);
		}
		else
		{
			j = 0;
			bytes_count = 0;
			if (test[i] > 127 && test[i] <= 2047)
			{
				j = 0;
				bytes_count = 2;
				shift = 6;
				while (j < bytes_count)
				{
					first[j] = test[i];
					j++;
				}
				j = 0;
				while (j < bytes_count)
				{
					res[j] = first[j] >> shift;
					if (j == 0)
						{
							res[j] = res[j] & 31;
							res[j] += 192;
						}
					else
					{
						res[j] = res[j] & 63;
						res[j] += 128;
					}
					shift -= 6;
					j++;
				}
				write(1, res, bytes_count);
			}
			else if (test[i] > 2047 && test[i] <= 65535)
			{
				j = 0;
				bytes_count = 3;
				shift = 12;
				while (j < bytes_count)
				{
					first[j] = test[i];
					j++;
				}
				j = 0;
				while (j < bytes_count)
				{
					res[j] = first[j] >> shift;
					if (j == 0)
						{
							res[j] = res[j] & 15;
							res[j] += 224;
						}
					else
					{
						res[j] = res[j] & 63;
						res[j] += 128;
					}
					shift -= 6;
					j++;
				}
				write(1, res, bytes_count);
			}
			else if (test[i] > 65535 && test[i] <= 1114111)
			{
				j = 0;
				bytes_count = 4;
				shift = 18;
				while (j < bytes_count)
				{
					first[j] = test[i];
					j++;
				}
				j = 0;
				while (j < bytes_count)
				{
					res[j] = first[j] >> shift;
					if (j == 0)
						{
							res[j] = res[j] & 7;
							res[j] += 240;
						}
					else
					{
						res[j] = res[j] & 63;
						res[j] += 128;
					}
					shift -= 6;
					j++;
				}
				write(1, res, bytes_count);
			}
		}
		i++;
	}
}
