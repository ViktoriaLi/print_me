#include "ft_printf.h"
#include <stdio.h>
	//sSpdDioOuUxXcC
	//%%
	//flags #0-+ and space
	//minimum field-width
	//the precision
	// flags hh, h, l, ll, j, et z.

void check_type(char type)
{
	int (type == 's' || type == 'S' || type == 'p' || type == 'D' ||
	 type == 'i' || type == 'o' || type == 'O' || type == 'u' ||
 	type == 'U' || type == 'x' || type == 'X' || type == 'c' || type == 'C')
		return (type);
	else
		return (0);
}

void check_size(char size)
{
}

void check_precision(char precision)
{
}

void check_width(char width)
{

}

int check_flags(char flag)
{
	if (flag == '+')
	{
		write(1, "+", 1);
		return (flag);
	}
	if (flag == '#' || flag == '0' || flag == '-' || flag == ' ')
	{
		return (flag);
	}
	return (0)
}


int ft_printf(const char *format, ...)
{

	int i = 0;
	va_list ap;
	char *p;
	int j = 0;
	p = (char *)format;
	va_start(ap, format);
	int d;
  	char a, c, *s;
  	wchar_t v, *w;
	while (p[i])
	{
		while (p[i] != '%' && p[i])
		{
			write(1, &p[i], 1);
			i++;
		}
		if (p[i] == '%')
		{
			i++;
			if (p[i] == '+')
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
			i++;
			}
		}
	va_end(ap);
	return (ft_strlen(p));
}

int main(void)
{
	printf("real   %%%s dsfdsfdsf %c %+d %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");
	ft_printf("custom %%%s dsfdsfdsf %c %+d %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");
	printf("real   %C\n", 't');
	ft_printf("custom %C\n", 't');
	printf("real   test \"my\"\n");
	ft_printf("custom test \"my\"\n");
	printf("etalon %d %05d\n", 10, 10);
	printf("real   %d %5d\n", 10, 10);


	//ft_printf("custom test \"my\"\n");
	return (0);
}
