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
//z > j > ll > l > h > hh
//для интов учитывать длину изначальную или после модификаторов?
//types Must contain at least one type. Example: "diouxX"
//length, you must mark it as "-|other_flags", otherwise it will be ignored. Example: "-|hh|ll"

//More detailed conversions management: eE, fF, gG, aA, n.
//More detailed flags management: *, $, L, ’.
//Non-existing flags management: %b to print in binary, %r to print a string of nonprintable
//characters, %k to print a date in any ordinary ISO format etc.
//Management of alter tools for colors, fd or other fun stuff like that :)

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
	while (str[*i] == '+' || str[*i] == '#' || str[*i] == '0' || str[*i] == '-' || str[*i] == ' '
		|| str[*i] == '\'')
	{
		j++;
		(*i)++;
	}
	tmp = (int *)malloc(sizeof(int) * (j + 1));
	tmp[j] = 0;
	*i = 0;
	while (k < j)
	{
		tmp[k] = str[*i];
		k++;
		(*i)++;
	}
	k = 0;
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
	if (if_flag(tmp, '\'', j))
	{
		flag[k] = '\'';
		k++;
	}
}

void argument_analize(t_argc *params, va_list ap)
{
	char c;
	if ((*params).specifier == 's' && (*params).length[0] != 'l')
		s_analizator(params, ap);
	else if ((*params).specifier == 'S' || ((*params).specifier == 's' && (*params).length[0] == 'l'))
		S_analizator(params, ap);
	else if ((*params).specifier == 'p')
		p_analizator(params, ap);
	else if ((*params).specifier == 'd' || (*params).specifier == 'i')
		d_analizator(params, ap);
	else if ((*params).specifier == 'D')
		d_analizator(params, ap);
	else if ((*params).specifier == 'o')
		o_analizator(params, ap);
	else if ((*params).specifier == 'O')
		o_analizator(params, ap);
	else if ((*params).specifier == 'u')
		d_analizator(params, ap);
	else if ((*params).specifier == 'U')
		d_analizator(params, ap);
	else if ((*params).specifier == 'x')
		x_analizator(params, ap);
	else if ((*params).specifier == 'X')
		x_analizator(params, ap);
	else if ((*params).specifier == 'c')
		c_analizator(params, ap);
	else if ((*params).specifier == 'C' || ((*params).specifier == 'c' && (*params).length[0] == 'l'))
		C_analizator(params, ap);
	else
	{
		c = (*params).specifier;
		write(1, &c, 1);
	}
}

void argument_save(char *argv, t_argc *params, va_list ap)
{
	int i = 0;
	int j = 0;
	int len = 0;
	check_flags(argv, &i, (*params).flag);
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
		argument_analize(params, ap);
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
	while (i < FLAG_LIMIT)
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
	struct_init(&params);
	params.res = 0;
	va_start(ap, format);
	while (format[i] && format[i] != '%')
	{
		write(1, &format[i], 1);
		params.res++;
		i++;
	}
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '%')
			{
				write(1, &format[i], 1);
				i++;
				params.res++;
				continue;
			}
			j = 0;
			while (format[i] && format[i] != '%')
			{
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
				params.one_arg[j] = format[i];
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
		//printf("RETURN %d\n", params.res);
		struct_init(&params);
		i = len;
	}
	va_end(ap);
	return (params.res);
}

//int main(void)
//{
	/*разный вывод
	printf("NUMBER %d\n", printf("% +0-5.15d", -2147483648));
	printf("NUMBER %d\n", ft_printf("% +-05.15d", -2147483648));
	мой принтф ставит пробел при лонгах printf("NUMBER %d\n", ft_printf("% -20.d", 2147483648));
	-000002147483648NUMBER 16
	0000-2147483648NUMBER 15
	кейс printf("NUMBER %d\n", printf("% +-0#10.5ls", "test")); возвращает -1
	кейс printf("NUMBER %d\n", printf("% -20d", 0)); должен быть пробел
	кейс printf("NUMBER %d\n", printf("% -20d", 0)); - не выводит число, только пробелы
	если нет точности, но есть флаг 0 - сделать вывод нолей
	ошибка на %-5.1s
	проверить что на  выводит printf("NUMBER %d\n", printf("@moulitest: %c", 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %c", 0));
	*/

	/*printf("NUMBER %d\n", printf("% -20.d", 0));
	printf("NUMBER %d\n", ft_printf("% -20.d", 0));
	printf("NUMBER %d\n", printf("% +-0#10.5ls", "test"));
	printf("NUMBER %d\n", ft_printf("% +-0#10.5ls", "test"));
	printf("NUMBER %d\n", printf("real   %%%010.20ls dsfdsfdsf %c %+d %+i %u %S|\n", L"string", 'c', 156, 651, 54646, L"abcdef"));
	printf("NUMBER %d\n", ft_printf("custom %%%010.20ls dsfdsfdsf %c %+d %+i %u %S|\n", L"string", 'c', 156, 651, 54646, L"abcdef"));
	printf("real   %%%010.20ls dsfdsfdsf %c %+d %+i %u %S|\n", L"string", 'c', 156, 651, 54646, L"abcdef");
	ft_printf("real   %%%010.20ls dsfdsfdsf %c %+d %+i %u %S|\n", L"string", 'c', 156, 651, 54646, L"abcdef");
	printf("real   %%%+- 0#10.20s dsfdsfdsf %c %d %i %u %S|\n", "string", 'c', 156, 651, 54646, L"abcdef");
	ft_printf("custom %%%+- 0#10.20hs dsfdsfdsf %c %d %i %u %S|\n", "string", 'c', 156, 651, 54646, L"abcdef");
	printf("real   |%lc|\n", 't');
	ft_printf("custom |%lc|\n", 't');
	printf("real   test \"my\"\n");
	ft_printf("custom test \"my\"\n");
	printf("real   %d %1d\n", 10, 10);
	ft_printf("custom %d %1d\n", 10, 10);
	printf("real   %d %.1d\n", 10, 10);
	ft_printf("custom %d %.1d\n", 10, 10);
	printf("real string   |%1.5s| |%-5.1s| left \n", "test string", "test string");
	ft_printf("custom string |%1.5s| |%-5.1s| left\n", "test string", "test string");
	printf("real   |%10c|\n", 't');
	ft_printf("custom |%10c|\n", 't');
	printf ("real   %+10.6i eretr\n", 123);
	ft_printf ("custom %+10.6i eretr\n", 123);
	printf ("real   %-*.*i eretr \n", 10, 6, 123);
	ft_printf ("custom %-*.*i eretr \n", 10, 6, 123);
	ft_printf("custom %%%s dsfdsfdsf %c %+lld %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");
	printf ("real   %+-# 0i eretr\n", 123);
	ft_printf ("custom %+-# 0i eretr\n", 123);
	printf ("real   %+++000  ---###   00050.17hhD eretr\n", 123);
	ft_printf ("custom %+++000  ---###   00050.17hhD eretr\n", 123);
	printf ("real   %U eretr\n", 123);
	ft_printf ("custom %U eretr\n", 123);
	printf ("real   %10x eretr\n", 1422);
	ft_printf ("custom %10x eretr\n", 1422);
	char *str;
	printf ("real   %p eretr\n", &str);
	ft_printf ("custom %p eretr\n", &str);
	printf ("real   % -010.5hhi eretr\n", 65);
	ft_printf ("custom % -010.5hhi eretr\n", 65);*/


	//не реализовано
	//ft_printf("%%");
	//ft_printf("%5%");
	//ft_printf("%.0%");
	//printf("%x\n", 0);
	//ft_printf("%x\n", 0);
	//printf("%X\n", 0);
	//ft_printf("%X\n", 0);
	//printf("%x\n", -42);
	//ft_printf("%x\n", -42);
	//printf("%X\n", -42);
	//ft_printf("%X\n", -42);
	//printf("%x\n", 4294967296);
	//ft_printf("%x\n", 4294967296);
	//printf("%X\n", 4294967296);
	//ft_printf("%X\n", 4294967296);


	//Тесты проходят
	/*printf("NUMBER %d\n", printf("this is a %s", "string"));
	printf("NUMBER %d\n", ft_printf("this is a %s", "string"));
	printf("NUMBER %d\n", printf("Line Feed %s", "\n"));
	printf("NUMBER %d\n", ft_printf("Line Feed %s", "\n"));
	char *string = "string";
	printf("NUMBER %d\n", printf("@moulitest: %s", NULL));
	printf("NUMBER %d\n", ft_printf("@moulitest: %s", NULL));
	printf("NUMBER %d\n", printf("%s %s", NULL, string));
	printf("NUMBER %d\n", ft_printf("%s %s", NULL, string));

	printf("NUMBER %d\n", printf("@moulitest: %c", 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %c", 0));

	printf("NUMBER %d\n", printf("the %d", 1));
	printf("NUMBER %d\n", ft_printf("the %d", 1));
	printf("NUMBER %d\n", printf("%+d", 0));
	printf("NUMBER %d\n", ft_printf("%+d", 0));
	printf("NUMBER %d\n", printf("%hd", 32767));
	printf("NUMBER %d\n", ft_printf("%hd", 32767));
	printf("NUMBER %d\n", printf("%hd", 32768));
	printf("NUMBER %d\n", ft_printf("%hd", 32768));
	printf("NUMBER %d\n", printf("%hhd", 127));
	printf("NUMBER %d\n", ft_printf("%hhd", 127));
	printf("NUMBER %d\n", printf("%hhd", 128));
	printf("NUMBER %d\n", ft_printf("%hhd", 128));
	printf("NUMBER %d\n", printf("%hhd", -128));
	printf("NUMBER %d\n", ft_printf("%hhd", -128));
	printf("NUMBER %d\n", printf("%hhd", -129));
	printf("NUMBER %d\n", ft_printf("%hhd", -129));
	printf("NUMBER %d\n", printf("%ld", 2147483647));
	printf("NUMBER %d\n", ft_printf("%ld", 2147483647));
	printf("NUMBER %d\n", printf("%ld", -2147483648));
	printf("NUMBER %d\n", ft_printf("%ld", -2147483648));
	printf("NUMBER %d\n", printf("@moulitest: %.d %.0d", 42, 43));
	printf("NUMBER %d\n", ft_printf("@moulitest: %.d %.0d", 42, 43));
	printf("NUMBER %d\n", printf("1@moulitest: %.5u", 42));
	printf("NUMBER %d\n", ft_printf("2@moulitest: %.5u", 42));
	printf("NUMBER %d\n", printf("%05d", 42));
	printf("NUMBER %d\n", ft_printf("%05d", 42));
	printf("NUMBER %d\n", printf("%0+5d", 42));
	printf("NUMBER %d\n", ft_printf("%0+5d", 42));
	printf("NUMBER %d\n", printf("%zd", -0));
	printf("NUMBER %d\n", ft_printf("%zd", -0));
	printf("NUMBER %d\n", printf("@moulitest: %.d %.0d", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %.d %.0d", 0, 0));
  printf("NUMBER %d\n", printf("@moulitest: %5.d %5.0d", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %5.d %5.0d", 0, 0));

	printf("NUMBER %d\n", printf("%05o", 42));
	printf("NUMBER %d\n", ft_printf("%05o", 42));
	printf("NUMBER %d\n", printf("%#6o", 2500));
	printf("NUMBER %d\n", ft_printf("%#6o", 2500));
	printf("NUMBER %d\n", printf("@moulitest: %.o %.o", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %.o %.0o", 0, 0));
	printf("NUMBER %d\n", printf("@moulitest: %5.o %5.0o", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %5.o %5.0o", 0, 0));
	printf("NUMBER %d\n", printf("@moulitest: %#.o %#.0o", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %#.o %#.0o", 0, 0));
	*/



	//Тесты не проходят;

	/*printf("NUMBER %d\n", printf("%05d", -42));
	printf("NUMBER %d\n", ft_printf("%05d", -42));
	printf("NUMBER %d\n", printf("%0+5d", -42));
  printf("NUMBER %d\n", ft_printf("%0+5d", -42));
	printf("NUMBER %d\n", printf("%-05d", 42));
 	printf("NUMBER %d\n", ft_printf("%-05d", 42));
	printf("NUMBER %d\n", printf("%-05d", -42));
	printf("NUMBER %d\n", ft_printf("%-05d", -42));
	printf("NUMBER %d\n", printf("%ld", 2147483648));
	printf("NUMBER %d\n", ft_printf("%ld", 2147483648));
	printf("NUMBER %d\n", printf("%ld", -2147483649));
  printf("NUMBER %d\n", ft_printf("%ld", -2147483649));
	printf("NUMBER %d\n", printf("%lld", 9223372036854775807));
  printf("NUMBER %d\n", ft_printf("%lld", 9223372036854775807));
	printf("NUMBER %d\n", printf("%lld", -9223372036854775808));
  printf("NUMBER %d\n", ft_printf("%lld", -9223372036854775808));
	printf("NUMBER %d\n", printf("%jd", 9223372036854775807));
  printf("NUMBER %d\n", ft_printf("%jd", 9223372036854775807));
	printf("NUMBER %d\n", printf("%jd", -9223372036854775808));
  printf("NUMBER %d\n", ft_printf("%jd", -9223372036854775808));
	printf("NUMBER %d\n", printf("%zd", 4294967295));
  printf("NUMBER %d\n", ft_printf("%zd", 4294967295));
	printf("NUMBER %d\n", printf("%zd", 4294967296));
  printf("NUMBER %d\n", ft_printf("%zd", 4294967296));
	printf("NUMBER %d\n", printf("%+10.5d", 4242));
  printf("NUMBER %d\n", ft_printf("%-+10.5d", 4242));
	printf("NUMBER %d\n", printf("%03.2d", 0));
  printf("NUMBER %d\n", ft_printf("%03.2d", 0));
	printf("NUMBER %d\n", printf("%03.2d", 1));
  printf("NUMBER %d\n", ft_printf("%03.2d", 1));
	printf("NUMBER %d\n", printf("%03.2d", -1));
  printf("NUMBER %d\n", ft_printf("%03.2d", -1));*/



		/*printf("NUMBER %d\n", printf("%+d", 4242424242424242424242));
	printf("NUMBER %d\n", ft_printf("%+d", 4242424242424242424242));


	printf("NUMBER %d\n", printf("%05d", -42));
	printf("NUMBER %d\n", ft_printf("%05d", -42));
	printf("NUMBER %d\n", printf("%0+5d", -42));
	printf("NUMBER %d\n", ft_printf("%0+5d", -42));

	printf("NUMBER %d\n", printf("%hd", −32768));
	printf("NUMBER %d\n", ft_printf("%hd", −32768));

	printf("NUMBER %d\n", printf("%hd", −32769));
	printf("NUMBER %d\n", ft_printf("%hd", −32769));

	printf("NUMBER %d\n", printf("%ld", 2147483648));
	printf("NUMBER %d\n", ft_printf("%ld", 2147483648));
	printf("NUMBER %d\n", printf("%ld", -2147483649));
	printf("NUMBER %d\n", ft_printf("%ld", -2147483649));

	printf("NUMBER %d\n", printf("%lld", 9223372036854775807));
	printf("NUMBER %d\n", ft_printf("%lld", 9223372036854775807));
	printf("NUMBER %d\n", printf("%lld", -9223372036854775808));
	printf("NUMBER %d\n", ft_printf("%lld", -9223372036854775808));
	printf("NUMBER %d\n", printf("%jd", 9223372036854775807));
	printf("NUMBER %d\n", ft_printf("%jd", 9223372036854775807));

	printf("NUMBER %d\n", printf("%jd", -9223372036854775808));
	printf("NUMBER %d\n", ft_printf("%jd", -9223372036854775808));
	printf("NUMBER %d\n", printf("%zd", 4294967295));
	printf("NUMBER %d\n", ft_printf("%zd", 4294967295));
	printf("NUMBER %d\n", printf("%zd", 4294967296));
	printf("NUMBER %d\n", ft_printf("%zd", 4294967296));
	printf("NUMBER %d\n", printf("%zd", -1));
	printf("NUMBER %d\n", ft_printf("%zd", -1));
	printf("NUMBER %d\n", printf("@moulitest: %.10d", -42));
	printf("NUMBER %d\n", ft_printf("@moulitest: %.10d", -42));
	printf("NUMBER %d\n", printf("%03.2d", -1));
	printf("NUMBER %d\n", ft_printf("%03.2d", -1));*/


	/*printf("NUMBER %d\n", printf("@moulitest: %.d %.0d", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %.d %.0d", 0, 0));
	printf("NUMBER %d\n", printf("@moulitest: %5.d %5.0d", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %5.d %5.0d", 0, 0));*/

	//u specifier doesn't work
	/*printf("NUMBER %d\n", printf("%u", -1));
	printf("NUMBER %d\n", ft_printf("%u", -1));
	printf("NUMBER %d\n", printf("%u", 4294967295));
	printf("NUMBER %d\n", ft_printf("%u", 4294967295));
	printf("NUMBER %d\n", printf("%5u", 4294967295));
	printf("NUMBER %d\n", ft_printf("%5u", 4294967295));
	printf("NUMBER %d\n", printf("%15u", 4294967295));
	printf("NUMBER %d\n", ft_printf("%15u", 4294967295));
	printf("NUMBER %d\n", printf("%-15u", 4294967295));
	printf("NUMBER %d\n", ft_printf("%-15u", 4294967295));
	printf("NUMBER %d\n", printf("%015u", 4294967295));
	printf("NUMBER %d\n", ft_printf("%015u", 4294967295));
	printf("NUMBER %d\n", printf("% u", 4294967295));
	printf("NUMBER %d\n", ft_printf("% u", 4294967295));
	printf("NUMBER %d\n", printf("%+u", 4294967295));
	printf("NUMBER %d\n", ft_printf("%+u", 4294967295));
	printf("NUMBER %d\n", printf("%lu", 4294967295));
	printf("NUMBER %d\n", ft_printf("%lu", 4294967295));
	printf("NUMBER %d\n", printf("%lu", 4294967296));
	printf("NUMBER %d\n", ft_printf("%lu", 4294967296));
	printf("NUMBER %d\n", printf("%lu", -42));
	printf("NUMBER %d\n", ft_printf("%lu", -42));
	printf("NUMBER %d\n", printf("%llu", 4999999999));
	printf("NUMBER %d\n", ft_printf("%llu", 4999999999));
	printf("NUMBER %d\n", printf("%ju", 4999999999));
	printf("NUMBER %d\n", ft_printf("%ju", 4999999999));
	printf("NUMBER %d\n", printf("%ju", 4294967296));
	printf("NUMBER %d\n", ft_printf("%ju", 4294967296));
	printf("NUMBER %d\n", printf("%U", 4294967295));
	printf("NUMBER %d\n", ft_printf("%U", 4294967295));
	printf("NUMBER %d\n", printf("%hU", 4294967296));
	printf("NUMBER %d\n", ft_printf("%hU", 4294967296));
	printf("NUMBER %d\n", printf("%U", 4294967296));
	printf("NUMBER %d\n", ft_printf("%U", 4294967296));
	*/

	//printf("NUMBER %d\n", printf("% -3.5o", 9876543));
	//printf("NUMBER %d\n", ft_printf("% -3.5o", 9876543));
	//char *str;
	//printf ("real   %#x eretr\n", 1232456);
	//ft_printf ("custom %#x eretr\n", 1232456);
	//printf ("real   %d eretr\n", &str);
	//ft_printf ("custom %d eretr\n", &str);
//}
