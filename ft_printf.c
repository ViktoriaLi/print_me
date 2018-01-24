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
	if (type == 's' || type == 'S' || type == 'p' || type == 'd' || type == 'D'
	|| type == 'i' || type == 'o' || type == 'O' || type == 'u' ||
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
		dest = ft_strcpy(dest, length);
	}
}

int check_precision(char *precision)
{
	return ft_atoi(precision);
}

int check_width(char *width)
{
	return (ft_atoi(width));
}

int check_flags(char flag)
{
	if (flag == '+' || flag == '#' || flag == '0' || flag == '-' || flag == ' ')
	{
		return (flag);
	}
	return (1);
}

void argument_analize(t_argc params, va_list ap)
{
	if (params.specifier == 's')
		s_analizator(params, ap);
	else if (params.specifier == 'S')
		S_analizator(params, ap);
	else if (params.specifier == 'p')
		p_analizator(params, ap);
	else if (params.specifier == 'd')
		d_analizator(params, ap);
	else if (params.specifier == 'D')
		D_analizator(params, ap);
	else if (params.specifier == 'i')
		i_analizator(params, ap);
	else if (params.specifier == 'o')
		o_analizator(params, ap);
	else if (params.specifier == 'O')
		O_analizator(params, ap);
	else if (params.specifier == 'u')
		u_analizator(params, ap);
	else if (params.specifier == 'U')
		U_analizator(params, ap);
	else if (params.specifier == 'x')
		x_analizator(params, ap);
	else if (params.specifier == 'X')
		X_analizator(params, ap);
	else if (params.specifier == 'c')
		c_analizator(params, ap);
	else if (params.specifier == 'C')
		C_analizator(params, ap);
	else
		write(1, &params.specifier, 1);
}

void argument_save(char *argv, t_argc *params, va_list ap)
{
	int i = 0;
	int j = 0;
	int len = 0;

	if (check_flags(argv[i]) != 1)
	{
		(*params).flag = argv[i];
		i++;
	}
	if (argv[i] == '*' || (argv[i] >= '0' && argv[i] <= '9'))
	{
		if (argv[i] == '*')
			(*params).width = '*';
		else
			(*params).width = check_width(&argv[i]);
		while (argv[i] == '*' || (argv[i] >= '0' && argv[i] <= '9'))
			i++;
	}
	if (argv[i] == '.' && (argv[i + 1] == '*' || (argv[i + 1] >= '0' &&
		argv[i + 1] <= '9')))
	{
		i++;
		if (argv[i] == '*')
			(*params).precision = '*';
		else
			(*params).precision = check_precision(&argv[i]);
		while (argv[i] == '*' || (argv[i] >= '0' && argv[i] <= '9'))
			i++;
	}
	else if (argv[i] == '.')
		i++;
	check_length(argv[i], argv[i + 1], (*params).length);
	if ((*params).length[0] != 0)
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
		argument_analize((*params), ap);
	}
	else
		write(1, &argv[i], 1);
}

void struct_init(t_argc *params)
{
	//if ((*params).one_arg != NULL)
		//free((*params).one_arg);
	(*params).one_arg = NULL;
	(*params).flag = '1';
  (*params).width = 0;
  (*params).precision = 0;
  (*params).length[0] = 0;
	(*params).length[1] = 0;
	(*params).length[2] = 0;
  (*params).specifier = 0;
	//if ((*params).left != NULL)
		//free((*params).left);
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
	while (p[i] && p[i] != '%')
	{
		write(1, &p[i], 1);
		i++;
	}
	while (p[i])
	{
		if (p[i] == '%')
		{
			i++;
			if (p[i] == '%')
			{
				write(1, &p[i], 1);
				i++;
				continue;
			}
			j = 0;
			while (p[i] && p[i] != '%')
			{
				//write(1, &p[i], 1);
				i++;
				j++;
			}
			len = i;
			params.one_arg = (char *)malloc(j + 1);
			params.one_arg[j] = 0;
			j--;
			i--;
			while (j >= 0)
			{
				params.one_arg[j] = p[i];
				j--;
				i--;
			}
			//printf("ARGUMENT %s\n", params.one_arg);
		}
		if (params.one_arg)
			argument_save(params.one_arg, &params, ap);
		/*printf("FLAG %c\n", params.flag);
		printf("WIDTH %d\n", params.width);
		printf("PRECISION %d\n", params.precision);
		printf("LENGTH %s\n", params.length);
		printf("SPECIFIER %c\n", params.specifier);
		printf("LEFT %s\n", params.left);*/
		struct_init(&params);
		i = len;
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
	printf ("real   %+10.6d eretr\n", 123);
	ft_printf ("custom %+10.6d eretr\n", 123);
	printf ("real   %-*.*d eretr \n", 10, 6, 123);
	ft_printf ("custom %-*.*d eretr \n", 10, 6, 123);
	//ft_printf("custom %%%s dsfdsfdsf %c %+lld %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");

	//ft_printf("custom test \"my\"\n");
	return (0);
}
