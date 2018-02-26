#include <stdio.h>
#include "ft_printf.h"

void	fprint_zeros(t_argc *params, t_forprint *elems, char *s, double d)
{
	int tmp;

	tmp = (*elems).lenf;

	if (s[0] != '0')
	{
		if ((*params).sign == '-' && s[0] != '-')
			write(1, "-", 1);
		write(1, (*elems).s, (*elems).len);
		write(1, ".", 1);
		if ((int)((d - (int)d) * 100000000) == 0)
			while (tmp--)
				  write(1, "0", 1);
			else
		  	write(1, (*elems).sf, (*elems).lenf);
		if (s[0] == '-')
			(*params).res--;
		if ((*elems).zeros > 0)
		{
			(*params).res += (*elems).zeros;
			while ((*elems).zeros--)
				write(1, "0", 1);
		}
	}
	else if ((*params).precision != 0)
		write(1, "0", 1);
}

void	print_float_left(char *s, t_argc *params, t_forprint *elems, double d)
{
	fif_space_flag(params, &elems->zeros, &elems->spaces);
	if ((*params).sign != '-' && if_flag((*params).flag, '+', FLAG_LIMIT) &&
		(*params).specifier != 'o' && (*params).specifier != 'O'
		&& (*params).specifier != 'u' && (*params).specifier != 'U')
	{
		(*params).res += 1;
		(*elems).spaces -= 1;
		write(1, "+", 1);
	}
	if ((*params).sign == '-' && (*elems).zeros > 0)
	{
		(*params).sign = 0;
		(*elems).spaces--;
		write(1, "-", 1);
		(*elems).zeros += 1;
	}
	fprint_zeros(params, elems, s, d);
	if ((*elems).spaces > 0)
	{
		(*params).res += (*elems).spaces;
		while ((*elems).spaces--)
			write(1, " ", 1);
	}
}

void	fif_space_flag(t_argc *params, int *zeros, int *spaces)
{
	if (if_flag((*params).flag, ' ', FLAG_LIMIT) && (*params).sign != '-'
		&& !if_flag((*params).flag, '+', FLAG_LIMIT)
		&& (*params).specifier != 'u' && (*params).specifier != 'U' &&
		(*params).specifier != 'o' && (*params).specifier != 'O')
	{
		(*params).res += 1;
		write(1, " ", 1);
		*spaces -= 1;
		if (!if_flag((*params).flag, '-', FLAG_LIMIT) &&
			if_flag((*params).flag, '0', FLAG_LIMIT)
			&& (*params).width > 0 && (*params).precision <= 0)
			*zeros -= 1;
	}
}

void	fprint_spaces(t_argc *params, int *zeros, int *spaces)
{
	if ((*params).sign != '-' && if_flag((*params).flag, '+', FLAG_LIMIT) &&
		(*params).specifier != 'o' && (*params).specifier != 'O')
	{
		(*spaces) -= 1;
		if ((*params).precision <= 0)
			(*zeros) -= 1;
	}
	if ((*spaces) > 0 && (*zeros) > 0)
	{
		if ((*params).sign == '-' && (*zeros) > 0)
			(*spaces)--;
		(*params).res += (*spaces);
		while ((*spaces)--)
			write(1, " ", 1);
	}
	if ((*spaces) > 0 && (*zeros) <= 0)
	{
		if ((*params).sign == '-' && (*zeros) > 0)
			(*spaces)--;
		(*params).res += (*spaces);
		while ((*spaces)--)
			write(1, " ", 1);
	}
}

void	print_float_right(char *s, t_argc *params, t_forprint *elems, double d)
{
	fif_space_flag(params, &elems->zeros, &elems->spaces);
	fprint_spaces(params, &elems->zeros, &elems->spaces);
	if ((*params).sign == '-' && (*elems).zeros > 0)
	{
		write(1, "-", 1);
		(*params).sign = 1;
		if ((*params).precision > 0 &&
			!if_flag((*params).flag, '0', FLAG_LIMIT))
			(*elems).zeros += 1;
	}
	if ((*params).sign != '-' && (*params).sign != 1 &&
		if_flag((*params).flag, '+', FLAG_LIMIT)
		&& (*params).specifier != 'o' && (*params).specifier != 'O'
		&& (*params).specifier != 'u' && (*params).specifier != 'U')
	{
		(*params).res += 1;
		write(1, "+", 1);
	}
	fprint_zeros(params, elems, s, d);
}

void	float_elems_count(t_argc *params, t_forprint *elems, double d)
{
	(*params).res += (*elems).len + (*elems).lenf + 1;
	//if ((*params).precision > 0)
		//(*elems).zeros = (*params).precision - (*elems).lenf;
	if ((*elems).zeros < 0 && if_flag((*params).flag, '0', FLAG_LIMIT)
		&& !if_flag((*params).flag, '-', FLAG_LIMIT)
		&& (*params).precision != 0)
		(*elems).zeros = (*params).width - (*elems).lenf;
	if ((*elems).zeros > 0 && (*params).width > 1)
		(*elems).spaces = (*params).width - (*elems).len - (*elems).lenf - (*elems).zeros - 1;
	if ((*elems).zeros <= 0 && (*params).width > 1)
		(*elems).spaces = (*params).width - (*elems).len - (*elems).lenf - 1;
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
		print_float_left((*elems).s, params, elems, d);
	else
		print_float_right((*elems).s, params, elems, d);
	print_left(params);
}

void		f_analizator(t_argc *params, va_list ap)
{
  double d;
	t_forprint	elems;
	unsigned long long fordiv;
	int i;

	fordiv = 10;
	i = 0;
  elems_init(&elems);
	check_stars(params, ap);
	d = va_arg(ap, double);
	/*printf("fff %f\n", d);
	printf("fff %f\n", (float)d);
	printf("fff %d\n", (unsigned int)d);
	printf("fff %d\n", (int)d);*/

	elems.s = ft_itoa((int)d);
	if ((*params).precision <= 0)
		elems.sf = ft_itoa((int)(((float)d - (unsigned int)d) * 100000000));
	else
	{
		while (i < ((*params).precision - 1))
		{
			fordiv *= 10;
			i++;
		}
		elems.sf = ft_itoa((int)(((float)d - (unsigned int)d) * fordiv));
	}

	//printf("fff %d\n", ((int)(((float)d - (int)((float)d)) * 100000000)));
	elems.len = ft_strlen(elems.s);
	if ((*params).precision < 0)
		elems.lenf = 6;
	else
		elems.lenf = (*params).precision ;
	//printf("sss %s\n", elems.s);
	//printf("sss %s\n", elems.sf);
	if (elems.sf[elems.lenf + 1] >= '7')
    elems.sf[elems.lenf]++;
  if (elems.sf[elems.lenf] >= '7')
    elems.sf[elems.lenf - 1]++;
  elems.sf[elems.lenf] = 0;
	//printf("sss %s\n", elems.s);
	//printf("sss %s\n", elems.sf);
float_elems_count(params, &elems, d);


}
