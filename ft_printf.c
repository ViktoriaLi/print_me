#include "ft_printf.h"
#include <stdio.h>
	//sSpdDioOuUxXcC
	//%%
	//flags #0-+ and space
	//minimum field-width
	//the precision
	// flags hh, h, l, ll, j, et z.

int check_specifier(char type)
{
	if (type == 's' || type == 'S' || type == 'p' || type == 'D' ||
	 type == 'i' || type == 'o' || type == 'O' || type == 'u' ||
 	type == 'U' || type == 'x' || type == 'X' || type == 'c' || type == 'C')
		return (type);
	else
		return (0);
}

void check_length(char length1, char length2, char *dest)
{
	char length[3];
	length[0] = length1;
	length[1] = length2;
	length[2] = 0;
	if (ft_strcmp(length, "hh") == 0 || ft_strcmp(length, "h") == 0 || ft_strcmp(length, "l") == 0
	|| ft_strcmp(length, "ll") == 0 || ft_strcmp(length, "j") == 0 || ft_strcmp(length, "z") == 0)
	{
		dest = length;
	}
		//return (length);
	//return (NULL);
}

int check_precision(char precision)
{
	return (0);
}

int check_width(char width)
{
	return (0);
}

int check_flags(char flag)
{
	if (flag == '+')
	/*{
		write(1, "+", 1);
		return (flag);
	}*/
	if (flag == '+' || flag == '#' || flag == '0' || flag == '-' || flag == ' ')
	{
		return (flag);
	}
	return (1);
}

void argument_analize(char *argv, t_argc *params)
{
	int i = 0;
	int j = 0;
	int len = 0;

	if (check_flags(argv[i]) != 1)
	{
		(*params).flag = argv[i];
		i++;
	}
if (check_width(argv[i]))
	{
		(*params).width = argv[i];
		i++;
	}
	if (check_precision(argv[i]))
	{
		(*params).precision = argv[i];
		i++;
	}
	check_length(argv[i], argv[i + 1], (*params).length);
	if ((*params).length)
	{
		if (ft_strlen((*params).length) == 1)
			i++;
		else
			i += 2;
	}
	if (check_specifier(argv[i]))
	{
		(*params).specifier = argv[i];
		i++;
		len = i;
		while (argv[i])
		{
			i++;
		}
		(*params).left = (char *)malloc(i - len + 1);
		(*params).left[i - len] = 0;
		j = i - len;
		while (i >= len)
		{
			(*params).left[j] = argv[i];
			j--;
			i--;
		}
	}
}

void struct_init(t_argc *params)
{
	(*params).one_arg = NULL;
	(*params).flag = '1';
  (*params).width = 0;
  (*params).precision = 0;
  (*params).length = NULL;
  (*params).specifier = 0;
	(*params).left = NULL;
}

int ft_printf(const char *format, ...)
{
	t_argc params;
	int i = 0;
	int j = 0;
	int len = 0;
	va_list ap;
	char *p;
	p = (char *)format;
	struct_init(&params);
	va_start(ap, format);
	int d;
  char a, c, *s;
	wchar_t v, *w;
	while (p[i] != '%' && p[i])
	{
		write(1, &p[i], 1);
		i++;
	}
	while (p[i])
	{
		if (p[i] == '%')
		{
			j = 0;
			while (p[i] != '%' && p[i])
			{
				write(1, &p[i], 1);
				i++;
				j++;
			}
			len = i;
			params.one_arg = (char *)malloc(j);
			params.one_arg[j] = 0;
			while (j >= 1)
			{
				params.one_arg[j] = p[i];
				j--;
				i--;
			}
			printf("ARGUMENT %s\n", params.one_arg);
		}
		if (params.one_arg)
			argument_analize(params.one_arg, &params);
		struct_init(&params);
		i = len + 1;
	}
			/*if (p[i] == '+')
			{
				if (p[i + 1] == 'd' || p[i + 1] == 'i')
				write(1, &p[i], 1);
				i++;
			}
			if(p[i] == 's')
			{
				s = va_arg(ap, char *);
				write(1, s, ft_strlen(s));
			}
			else if(p[i] == 'd' || p[i] == 'i' || p[i] == 'u')
			{
				d = va_arg(ap, int);
				ft_putnbr(d);
			}
			else if(p[i] == 'c')
			{
				c = va_arg(ap, int);
      			write(1, &c, 1);
			}
			else if(p[i] == 'C')
			{
				v = va_arg(ap, wchar_t);
      			write(1, &v, 1);
			}
			else if(p[i] == 'S')
			{
				w = va_arg(ap, wchar_t *);
				j = 0;
				while (w[j])
				{
					write(1, &w[j], 1);
					j += 1;
				}
			}
			else
				write(1, &p[i], 1);
			i++;*/
	va_end(ap);
	return (ft_strlen(p));
}

int main(void)
{
	/*printf("real   %%%s dsfdsfdsf %c %+d %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");
	ft_printf("custom %%%s dsfdsfdsf %c %+d %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");
	printf("real   %C\n", 't');
	ft_printf("custom %C\n", 't');
	printf("real   test \"my\"\n");
	ft_printf("custom test \"my\"\n");
	printf("etalon %d %05d\n", 10, 10);
	printf("real   %d %5d\n", 10, 10);*/
	ft_printf("custom %%%s dsfdsfdsf %c %+d %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");

	//ft_printf("custom test \"my\"\n");
	return (0);
}
