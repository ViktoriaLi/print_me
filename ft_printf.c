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
    //while (format[i] != '%' && format[i])
    	//write(1, format[i], 1);
	while (format[i])
	{
		if(format[i] == 's')
		{
			s = va_arg(ap, char *);
            printf("string %hsssedfdrtrd\n", s);

		}
		if(format[i] == 'd')
		{
			d = va_arg(ap, int);
            printf("int %d\n", d);
		}
		if(format[i] == 'c')
		{
			c = va_arg(ap, int);
            printf("char %c\n", c);
		}
		i++;
	}
	va_end(ap);
	return (ft_strlen(format));
}

int main(void)
{
	ft_printf("%s%c", "d", 's');
	//printf("%d\n", printf("intыфваывавыа%d\n", 12));
	return (0);
}