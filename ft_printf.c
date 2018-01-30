#include "ft_printf.h"
#include <stdio.h>
	//sSpdDioOuUxXcC
	//%%
	//flags #0-+ and space
	//minimum field-width
	//the precision
	// flags hh, h, l, ll, j, et z.
//flag ' ' is ignored when flag '+' is present
//flag '0' is ignored when flag '-' is present
//если спецсимволы типа перевод строки передан как аргукмент в строку, он должен быть напечатан


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
	if (ft_strcmp(length, "hh") == 0 || ft_strcmp(length, "ll") == 0)
		dest = ft_strcpy(dest, length);
	else if (length[0] == 'h' || length[0] == 'l' ||
		length[0] == 'j' || length[0] == 'z')
		dest[0] = length[0];
}

int check_precision(char *precision)
{
	return ft_atoi(precision);
}

int check_width(char *width)
{
	return (ft_atoi(width));
}

void check_flags(char *str, int *i, int *flag)
{
	int j;
	int k;
	int *tmp;

	j = 0;
	k = 0;
	tmp = NULL;
	while ((str[*i] == '+' || str[*i] == '#' || str[*i] == '0' || str[*i] == '-' || str[*i] == ' '))
	{
		tmp[j] = str[*i];
		j++;
		(*i)++;
	}
	if (if_flag(tmp, '+', j))
	{
		flag[k] = '+';
		k++;
	}
	if (if_flag(tmp, '#', j))
	{
		flag[k] = '#';
		k++;
	}
	if (if_flag(tmp, '0', j))
	{
		flag[k] = '0';
		k++;
	}
	if (if_flag(tmp, '-', j))
	{
		flag[k] = '-';
		k++;
	}
	if (if_flag(tmp, ' ', j))
	{
		flag[k] = ' ';
		k++;
	}
}

void argument_analize(t_argc params, va_list ap)
{
	if (params.specifier == 's' && params.length[0] != 'l')
		s_analizator(params, ap);
	else if (params.specifier == 'S' || (params.specifier == 's' && params.length[0] == 'l'))
		S_analizator(params, ap);
	else if (params.specifier == 'p')
		p_analizator(params, ap);
	else if (params.specifier == 'd' || params.specifier == 'i')
		d_analizator(params, ap);
	else if (params.specifier == 'D')
		d_analizator(params, ap);
	//else if (params.specifier == 'i')
		//i_analizator(params, ap);
	else if (params.specifier == 'o')
		o_analizator(params, ap);
	else if (params.specifier == 'O')
		o_analizator(params, ap);
	else if (params.specifier == 'u')
		d_analizator(params, ap);
	else if (params.specifier == 'U')
		d_analizator(params, ap);
	else if (params.specifier == 'x')
		x_analizator(params, ap);
	else if (params.specifier == 'X')
		x_analizator(params, ap);
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

	check_flags(argv, &i, (*params).flag);
	/*printf("int flag %d %d %d %d %d ", params->flag[0], params->flag[1],
		params->flag[2], params->flag[3], params->flag[4]);*/
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
	int i;

	i = 0;
	(*params).one_arg = NULL;
	while (i < 6)
	{
		(*params).flag[i] = 0;
		i++;
	}
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
		/*printf("FLAG %c %c %c %c %c\n", (char)params.flag[0], (char)params.flag[1],
		(char)params.flag[2], (char)params.flag[3], (char)params.flag[4]);
		printf("WIDTH %d\n", params.width);
		printf("PRECISION %d\n", params.precision);
		printf("LENGTH %s\n", params.length);
		printf("SPECIFIER %c\n", params.specifier);
		printf("LEFT %s\n", params.left);*/
		//printf("RES %d\n", ft_strcmp(params.length, "hh"));
		struct_init(&params);
		i = len;
	}
	va_end(ap);
	return (ft_strlen(p));
}

//int main(void)
//{
	/*printf("real   %%%010.20ls dsfdsfdsf %c %+d %+i %u %S|\n", L"string", 'c', 156, 651, 54646, L"abcdef");
	ft_printf("custom %%%010.20ls dsfdsfdsf %c %+d %+i %u %S|\n", L"string", 'c', 156, 651, 54646, L"abcdef");*/
	/*printf("real   |%lc|\n", 't');
	ft_printf("custom |%lc|\n", 't');*/
	/*printf("real   test \"my\"\n");
	ft_printf("custom test \"my\"\n");
	printf("real   %d %1d\n", 10, 10);
	ft_printf("custom %d %1d\n", 10, 10);
	printf("real   %d %.1d\n", 10, 10);
	ft_printf("custom %d %.1d\n", 10, 10);
	printf("real string   |%1.5s| |%-5.1s| left \n", "test string", "test string");
	ft_printf("custom string |%1.5s| |%-5.1s| left\n", "test string", "test string");*/
	//printf("real   |%10c|\n", 't');
	//ft_printf("custom |%10c|\n", 't');
	/*printf ("real   %+10.6i eretr\n", 123);
	ft_printf ("custom %+10.6i eretr\n", 123);*/
	//printf ("real   %-*.*i eretr \n", 10, 6, 123);
	//ft_printf ("custom %-*.*i eretr \n", 10, 6, 123);
	//ft_printf("custom %%%s dsfdsfdsf %c %+lld %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");
	/*printf ("real   %+-# 0i eretr\n", 123);
	ft_printf ("custom %+-# 0i eretr\n", 123);*/
	/*printf ("real   %+++000  ---###   00050.17hhD eretr\n", 123);
	ft_printf ("custom %+++000  ---###   00050.17hhD eretr\n", 123);
	printf ("real   %U eretr\n", 123);
	ft_printf ("custom %U eretr\n", 123);*/
	/*printf ("real   %10x eretr\n", 1422);
	ft_printf ("custom %10x eretr\n", 1422);*/
	//char *str;
	//printf ("real   %p eretr\n", &str);
	//ft_printf ("custom %p eretr\n", &str);
	/*printf ("real   % -010.5hhi eretr\n", 65);
	ft_printf ("custom % -010.5hhi eretr\n", 65);
	return (0);*/

	//Тесты не проходят;
	//ft_printf("%%");
	//ft_printf("%5%");
	//ft_printf("Line Feed %s\n", "\n");

	/*ft_printf("%x\n", 0);
	ft_printf("%X\n", 0);
	ft_printf("%x\n", -42);
	ft_printf("%X\n", -42);
	ft_printf("%x\n", 4294967296);
	ft_printf("%X\n", 4294967296);
	ft_printf("%s\n", "abc");
	ft_printf("%s\n", "this is a string");
	ft_printf("%s \n", "this is a string");
	ft_printf("%s  \n", "this is a string");
	ft_printf("this is a %s\n", "string");
	ft_printf("%s is a string\n", "this");
	ft_printf("Line Feed %s\n", "\n");
	ft_printf("%10s is a string\n", "this");
	ft_printf("%.2s is a string\n", "this");*/
	//ft_printf("%10s is a string\n", "");
	//ft_printf("%.2s is a string\n", "");
	/*ft_printf("%u", 0);
	ft_printf("%u", 1);
	ft_printf("%u", -1);
	ft_printf("%u", 4294967295);
	ft_printf("%u", 4294967296);
	ft_printf("%5u", 4294967295);
	ft_printf("%15u", 4294967295);
	ft_printf("%-15u", 4294967295);
	ft_printf("%015u", 4294967295);
	ft_printf("% u", 4294967295);
	ft_printf("%+u", 4294967295);
	ft_printf("%lu", 4294967295);
	ft_printf("%lu", 4294967296);
	ft_printf("%lu", -42);
	ft_printf("%llu", 4999999999);
	ft_printf("%ju", 4999999999);
	ft_printf("%ju", 4294967296);
	ft_printf("%U", 4294967295);
	ft_printf("%hU", 4294967296);
	ft_printf("%U", 4294967296);
	ft_printf("@moulitest: %.5u", 42);*/
//}
