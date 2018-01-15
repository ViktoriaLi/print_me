#include "ft_printf.h"
#include <stdio.h>

	//sSpdDioOuUxXcC
	//%%
	//flags #0-+ and space
	//minimum field-width
	//the precision
	// flags hh, h, l, ll, j, et z.

int ft_printf(const char *format, ...)
{

	int i = 0;
	va_list ap;
	va_start(ap, format);
	int d;
  char c, *s;
  printf("format %s\n", format);
	while (format[i])
	{
		while (format[i] != '%' && format[i])
		{
			write(1, &format[i], 1);
			i++;
		}
		if(format[i] == '%')
		{
			i++;
			if(format[i] == '%')
			{
				c = va_arg(ap, int);
				write(1, &c, 1);
				i++;
			}
			if(format[i] == 's')
			{
				s = va_arg(ap, char *);
				write(1, s, ft_strlen(s));
			}
			if(format[i] == 'd')
			{
				d = va_arg(ap, int);
				ft_putnbr(d);
			}
			if(format[i] == 'c')
			{
				c = va_arg(ap, int);
	      write(1, &c, 1);
			}
			i++;
		}
	}
	va_end(ap);
	return (ft_strlen(format));
}

int main(void)
{
	ft_printf("%s%c", "d", 's');
	printf("\n%s%c", "d", 's');
	//printf("%d\n", printf("intыфваывавыа%d\n", 12));
	return (0);
}
