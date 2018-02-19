#include "ft_printf.h"
#include <stdio.h>
# include <locale.h>

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
//flag '0' results in undefined behavior with 'S' conversion specifier

//More detailed conversions management: eE, fF, gG, aA, n.
//More detailed flags management: *, $, L, ’.
//Non-existing flags management: %b to print in binary, %r to print a string of nonprintable
//characters, %k to print a date in any ordinary ISO format etc.
//Management of alter tools for colors, fd or other fun stuff like that :)
//перевести все в итоа, для ансайнд - сайз т, для сайнд - интмакс, но внутри привести к сайз т без минуса, а минус сохранить
//не указана тип, но есть буква - выводится она, если есть только число - это считается шириной - проверить остельные флаги без типа
// Большас С - нужно ли приводить к винт_т?
//проверить, если спецификаторов больше чем аргументов, не вылетает ли мой принтф, сделать проверку

int check_specifier(char type)
{
	if (type == 's' || type == 'S' || type == 'p' || type == 'd' || type == 'D'
	|| type == 'i' || type == 'o' || type == 'O' || type == 'u' || type == 'U'
	|| type == 'x' || type == 'X' || type == 'c' || type == 'C' || type == 'e'
	|| type == 'E' || type == 'f' || type == 'F' || type == 'g' || type == 'G'
	|| type == 'a' || type == 'A' || type == 'n')
		return (type);
	else
		return (0);
}

void check_length(char *length, int *i, char *dest)
{
	int j;
	int len;
	int h_count;
	int l_count;

	j = 0;
	len = 0;
	h_count = 0;
	l_count = 0;
	while (length[j] == 'h' || length[j] == 'l' || length[j] == 'j' || length[j] == 'z')
	{
		j++;
		(*i)++;
	}
	len = j;
	j = 0;
	if (ft_len_strnstr(length, "ll", len) && dest[0] != 'z' && dest[0] != 'j')
	{
		dest[0] = 'l';
		dest[1] = 'l';
	}
	if (ft_len_strnstr(length, "hh", len) && dest[0] != 'l' && dest[0] != 'z' && dest[0] != 'j')
	{
		dest[0] = 'h';
		dest[1] = 'h';
	}
	while (j < len)
	{
		if (length[j] == 'z')
		{
			dest[0] = 'z';
			dest[1] = 0;
		}
		if (length[j] == 'j' && dest[0] != 'z')
		{
			dest[0] = 'j';
			dest[1] = 0;
		}
		if (length[j] == 'h')
			h_count++;
		if (length[j] == 'l')
			l_count++;
		j++;
	}
	if (h_count % 2 != 0 && dest[0] != 'l' && dest[0] != 'z' && dest[0] != 'j')
		{
			dest[0] = 'h';
			dest[1] = 0;
		}
	if (l_count % 2 != 0 && dest[0] != 'l' && dest[0] != 'z' && dest[0] != 'j')
		{
			dest[0] = 'l';
			dest[1] = 0;
		}
}

void check_flags(char *str, int *i, int *flag)
{
	int j;
	int k;
	int *tmp;

	j = 0;
	k = 0;
	tmp = NULL;
	while (str[*i] == '+' || str[*i] == '#' || str[*i] == '0'
		|| str[*i] == '-' || str[*i] == ' '	|| str[*i] == '\'')
	{
		j++;
		(*i)++;
	}
	tmp = (int *)malloc(sizeof(int) * (j + 1));
	tmp[j] = 0;
	*i = 0;
	while (k < j)
		tmp[k++] = str[(*i)++];
	k = 0;
	if (if_flag(tmp, '+', j))
		flag[k++] = '+';
	if (if_flag(tmp, '#', j))
		flag[k++] = '#';
	if (if_flag(tmp, '0', j))
		flag[k++] = '0';
	if (if_flag(tmp, '-', j))
		flag[k++] = '-';
	if (if_flag(tmp, ' ', j))
		flag[k++] = ' ';
	if (if_flag(tmp, '\'', j))
		flag[k++] = '\'';
	if (tmp)
		free(tmp);
}

void argument_analize(t_argc *params, va_list ap)
{
	int *n_value;

	n_value = NULL;
	if ((*params).specifier == 's' && (*params).length[0] != 'l')
		s_analizator(params, ap);
	else if ((*params).specifier == 'S' || ((*params).specifier == 's'
		&& (*params).length[0] == 'l'))
		S_analizator(params, ap);
	else if ((*params).specifier == 'd' || (*params).specifier == 'i'
		|| (*params).specifier == 'D')
		d_analizator(params, ap);
	else if ((*params).specifier == 'o' || (*params).specifier == 'O')
		o_analizator(params, ap);
	else if ((*params).specifier == 'u' || (*params).specifier == 'U')
		u_analizator(params, ap);
	else if ((*params).specifier == 'x' || (*params).specifier == 'X'
		|| (*params).specifier == 'p')
		x_analizator(params, ap);
	else if ((*params).specifier == 'c' && (*params).length[0] != 'l')
		c_analizator(params, ap);
	else if ((*params).specifier == 'C' || ((*params).specifier == 'c'
		&& (*params).length[0] == 'l'))
		C_analizator(params, ap);
	else if ((*params).specifier == 'n')
	{
		n_value = va_arg(ap, int *);
		*n_value = (*params).res;
	}


}

void check_star_anywhere(char c, int *i, int *param)
{
	if (c == '*')
	{
		*param = '*';
		(*i)++;
	}
}

void argument_save(char *argv, t_argc *params, va_list ap)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = 0;
	check_star_anywhere(argv[i], &i, &params->width);
	check_flags(argv, &i, (*params).flag);
	check_star_anywhere(argv[i], &i, &params->width);
	if ((argv[i] >= '0' && argv[i] <= '9'))
	{
		(*params).star_width = (*params).width;
		(*params).width = ft_atoi(&argv[i]);
		while (argv[i] >= '0' && argv[i] <= '9')
			i++;
	}
	check_star_anywhere(argv[i], &i, &params->width);
	if (argv[i] == '.')
	{
		(*params).precision = 0;
		i++;
		check_star_anywhere(argv[i], &i, &params->precision);
		if (argv[i] >= '0' && argv[i] <= '9')
		{
			if ((*params).precision != '*')
				(*params).precision = ft_atoi(&argv[i]);
			else if ((*params).width != '*')
				(*params).width = ft_atoi(&argv[i]);
		}
		while ((argv[i] >= '0' && argv[i] <= '9'))
			i++;
	}
	else if (argv[i] == '.')
		i++;
	check_star_anywhere(argv[i], &i, &params->width);
	check_length(&argv[i], &i, (*params).length);
	check_star_anywhere(argv[i], &i, &params->width);
	if (check_specifier(argv[i]))
	{
		(*params).specifier = argv[i++];
		len = i;
		while (argv[i])
			i++;
		(*params).left = (char *)malloc(i - len + 1);
		(*params).left[i - len] = 0;
		j = i - len;
		(*params).left_len = j;
		while (i >= len)
			(*params).left[j--] = argv[i--];
		argument_analize(params, ap);
		i++;
	}
	else if ((*params).specifier == '%' || ((argv[i] >= 65
		&& argv[i] <= 90) || (argv[i] >= 97 && argv[i] <= 122)))
	{
		if ((*params).specifier != '%')
			(*params).specifier = argv[i];
		c_analizator(params, ap);
		i++;
	}
	if (!(*params).left)
		while (argv[i])
		{
			write(1, &argv[i++], 1);
			(*params).res++;
		}
}

void struct_init(t_argc *params)
{
	int i;

	i = 0;
	(*params).one_arg = NULL;
	while (i < FLAG_LIMIT)
		(*params).flag[i++] = 0;
  (*params).width = 0;
	(*params).star_width = 0;
  (*params).precision = -1;
  (*params).length[0] = 0;
	(*params).length[1] = 0;
	(*params).length[2] = 0;
  (*params).specifier = 0;
	(*params).left = NULL;
	(*params).left_len = 0;
	(*params).reserve = NULL;
	(*params).sign = 0;
}

int ft_printf(const char *format, ...)
{
	t_argc params;
	int i;
	int j;
	int len;
	va_list ap;

	i = 0;
	len = 0;
	params.res = 0;
	va_start(ap, format);
	while (format[i] && format[i] != '%')
	{
		write(1, &format[i++], 1);
		params.res++;
	}
	while (format[i])
	{
		if (format[i] == '%')
		{
			struct_init(&params);
			if (format[++i] == '%')
			{
				write(1, &format[i++], 1);
				params.res++;
				continue;
			}
			j = 0;
			while (format[i] && format[i] != '%')
			{
				i++;
				j++;
			}
			if (format[i] == '%')
				params.specifier = '%';
			len = i--;
			params.one_arg = (char *)malloc(j + 1);
			params.one_arg[j--] = 0;
			while (j >= 0)
				params.one_arg[j--] = format[i--];
			i = len;
		}
		else
		{
			while (format[i] && format[i] != '%')
			{
				write(1, &format[i++], 1);
				params.res++;
			}
		}
		if (params.one_arg)
			argument_save(params.one_arg, &params, ap);
		/*printf("ARGUMENT %s\n", params.one_arg);
		printf("FLAG %c %c %c %c %c\n", (char)params.flag[0], (char)params.flag[1],
		(char)params.flag[2], (char)params.flag[3], (char)params.flag[4]);
		printf("WIDTH %d\n", params.width);
		printf("PRECISION %d\n", params.precision);
		printf("LENGTH %s\n", params.length);
		printf("SPECIFIER %c\n", params.specifier);
		printf("LEFT %s\n", params.left);*/
		/*printf("RETURN %d\n", params.res);*/
		ft_strdel(&params.left);
		ft_strdel(&params.one_arg);
	}
	va_end(ap);
	return (params.res);
}

/*int main(void)
{
	setlocale (LC_ALL, "");*/
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
	не работает корректно строка ft_printf("real   %%%010.20ls dsfdsfdsf %c %+d %+i %u %S|", L"string", 'c', 156, 651, 54646, L"abcdef"));
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


	/*printf("NUMBER %d\n", printf("%5%"));
	printf("NUMBER %d\n", ft_printf("%5%"));
	printf("NUMBER %d\n", printf("%.0%"));
	printf("NUMBER %d\n", ft_printf("%.0%"));
	printf("NUMBER %d\n", printf("%-5%"));
	printf("NUMBER %d\n", ft_printf("%-5%"));*/

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

	printf("NUMBER %d\n", printf("%03.2d", -1));
  printf("NUMBER %d\n", ft_printf("%03.2d", -1));
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
	printf("NUMBER %d\n", printf("%-05d", 42));
	printf("NUMBER %d\n", ft_printf("%-05d", 42));
	printf("NUMBER %d\n", printf("%-05d", -42));
	printf("NUMBER %d\n", ft_printf("%-05d", -42));
	printf("NUMBER %d\n", printf("%-+10.5d", 4242));
  printf("NUMBER %d\n", ft_printf("%-+10.5d", 4242));
	printf("NUMBER %d\n", printf("%+10.5d", 4242));
	printf("NUMBER %d\n", ft_printf("%+10.5d", 4242));
	printf("NUMBER %d\n", printf("%-+10.5d", 4242));
  printf("NUMBER %d\n", ft_printf("%-+10.5d", 4242));
	printf("NUMBER %d\n", printf("%03.2d", 0));
  printf("NUMBER %d\n", ft_printf("%03.2d", 0));
	printf("NUMBER %d\n", printf("%03.2d", 1));
  printf("NUMBER %d\n", ft_printf("%03.2d", 1));
	printf("NUMBER %d\n", printf("%03.2d", 0));
  printf("NUMBER %d\n", ft_printf("%03.2d", 0));
	printf("NUMBER %d\n", printf("%03.2d", 1));
  printf("NUMBER %d\n", ft_printf("%03.2d", 1));
	printf("NUMBER %d\n", printf("%hd", −32768));
	printf("NUMBER %d\n", ft_printf("%hd", −32768));
	printf("NUMBER %d\n", printf("%hd", −32769));
	printf("NUMBER %d\n", ft_printf("%hd", −32769));
	printf("NUMBER %d\n", printf("%zd", -1));
	printf("NUMBER %d\n", ft_printf("%zd", -1));
	printf("NUMBER %d\n", printf("@moulitest: %.10d", -42));
	printf("NUMBER %d\n", ft_printf("@moulitest: %.10d", -42));
	printf("NUMBER %d\n", printf("%05d", -42));
	printf("NUMBER %d\n", ft_printf("%05d", -42));
	printf("NUMBER %d\n", printf("%0+5d", -42));
  printf("NUMBER %d\n", ft_printf("%0+5d", -42));

	printf("NUMBER %d\n", printf("%05o", 42));
	printf("NUMBER %d\n", ft_printf("%05o", 42));
	printf("NUMBER %d\n", printf("%#6o", 2500));
	printf("NUMBER %d\n", ft_printf("%#6o", 2500));
	printf("NUMBER %d\n", printf("@moulitest: %.0o %.0o", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %.0o %.0o", 0, 0));
	printf("NUMBER %d\n", printf("@moulitest: %5.o %5.0o", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %5.o %5.0o", 0, 0));
	printf("NUMBER %d\n", printf("@moulitest: %#.o %#.0o", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %#.o %#.0o", 0, 0));
	printf("NUMBER %d\n", printf("%-05o", 2500));
	printf("NUMBER %d\n", ft_printf("%-05o", 2500));

	printf("NUMBER %d\n", printf("%10x", 42));
	printf("NUMBER %d\n", ft_printf("%10x", 42));
  printf("NUMBER %d\n", printf("%-10x", 42));
	printf("NUMBER %d\n", ft_printf("%-10x", 42));
	printf("NUMBER %d\n", printf("%010x", 542));
	printf("NUMBER %d\n", ft_printf("%010x", 542));
  printf("NUMBER %d\n", printf("%-15x", 542));
	printf("NUMBER %d\n", ft_printf("%-15x", 542));
  printf("NUMBER %d\n", printf("%2x", 542));
	printf("NUMBER %d\n", ft_printf("%2x", 542));
	printf("NUMBER %d\n", printf("%5.2x", 5427));
	printf("NUMBER %d\n", ft_printf("%5.2x", 5427));
	printf("NUMBER %d\n", printf("%#x", 0));
  printf("NUMBER %d\n", ft_printf("%#x", 0));
	printf("NUMBER %d\n", printf("%#8x", 42));
	printf("NUMBER %d\n", ft_printf("%#8x", 42));
  printf("NUMBER %d\n", printf("%#08x", 42));
	printf("NUMBER %d\n", ft_printf("%#08x", 42));
  printf("NUMBER %d\n", printf("%#-08x", 42));
	printf("NUMBER %d\n", ft_printf("%#-08x", 42));
	printf("NUMBER %d\n", printf("@moulitest: %#.x %#.0x", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %#.x %#.0x", 0, 0));
  printf("NUMBER %d\n", printf("@moulitest: %.x %.0x", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %.x %.0x", 0, 0));
  printf("NUMBER %d\n", printf("@moulitest: %5.x %5.0x", 0, 0));
	printf("NUMBER %d\n", ft_printf("@moulitest: %5.x %5.0x", 0, 0));
	printf("NUMBER %d\n", printf("%x", -42));
	printf("NUMBER %d\n", ft_printf("%x", -42));
  printf("NUMBER %d\n", printf("%X", -42));
	printf("NUMBER %d\n", ft_printf("%X", -42));
	*/

	//Тесты не проходят;

	//printf("NUMBER %d\n", printf("%lld", 9223372036854775807));
  //printf("NUMBER %d\n", ft_printf("%lld", 9223372036854775807));
	//printf("NUMBER %d\n", printf("%jd", 9223372036854775807));
  //printf("NUMBER %d\n", ft_printf("%jd", 9223372036854775807));

	/*
	printf("NUMBER %d\n", printf("%+u", 4294967295));
	printf("NUMBER %d\n", ft_printf("%+u", 4294967295));
	printf("NUMBER %d\n", printf("%lu", -42));
	printf("NUMBER %d\n", ft_printf("%lu", -42));
	printf("NUMBER %d\n", printf("%hU", 4294967296));
	printf("NUMBER %d\n", ft_printf("%hU", 4294967296));
	printf("NUMBER %d\n", printf("%U", 4294967296));
	printf("NUMBER %d\n", ft_printf("%U", 4294967296));*/

	//printf("NUMBER %d\n", ft_printf("%U", 4294967296));

	/*printf("NUMBER %d\n", printf("%jx", -4294967296));
	printf("NUMBER %d\n", ft_printf("%jx", -4294967296));
  printf("NUMBER %d\n", printf("%jx", -4294967297));
	printf("NUMBER %d\n", ft_printf("%jx", -4294967297));*/

	/*printf("NUMBER %d\n", printf("%lx", 4294967296));
	printf("NUMBER %d\n", ft_printf("%lx", 4294967296));
  printf("NUMBER %d\n", printf("%llX", 4294967296));
	printf("NUMBER %d\n", ft_printf("%llX", 4294967296));
	printf("NUMBER %d\n", printf("%jx", 4294967295));
	printf("NUMBER %d\n", ft_printf("%jx", 4294967295));
  printf("NUMBER %d\n", printf("%jx", 4294967296));
	printf("NUMBER %d\n", ft_printf("%jx", 4294967296));
  printf("NUMBER %d\n", printf("%llx", 9223372036854775807));
	printf("NUMBER %d\n", ft_printf("%llx", 9223372036854775807));
  printf("NUMBER %d\n", printf("%llx", 9223372036854775808));
	printf("NUMBER %d\n", ft_printf("%llx", 9223372036854775808));
	printf("NUMBER %d\n", printf("%#llx", 9223372036854775807));
	printf("NUMBER %d\n", ft_printf("%#llx", 9223372036854775807));*/

	/*printf("NUMBER %d\n", printf("%ld", 2147483648));
	printf("NUMBER %d\n", ft_printf("%ld", 2147483648));
	printf("NUMBER %d\n", printf("%ld", -2147483649));
  printf("NUMBER %d\n", ft_printf("%ld", -2147483649));

	printf("NUMBER %d\n", printf("%zd", 4294967295));
  printf("NUMBER %d\n", ft_printf("%zd", 4294967295));
	printf("NUMBER %d\n", printf("%zd", 4294967296));
  printf("NUMBER %d\n", ft_printf("%zd", 4294967296));*/

	/*printf("NUMBER %d\n", printf("%05d", -42));
	printf("NUMBER %d\n", ft_printf("%05d", -42));
	printf("NUMBER %d\n", printf("%0+5d", -42));
	printf("NUMBER %d\n", ft_printf("%0+5d", -42));
	printf("NUMBER %d\n", printf("%03.2d", -1));
  printf("NUMBER %d\n", ft_printf("%03.2d", -1));
	*/

  //printf("NUMBER %d\n", printf("%+d", 4242424242424242424242));
	//printf("NUMBER %d\n", ft_printf("%+d", 4242424242424242424242));
	/*printf("NUMBER %d\n", printf("%05d", -42));
	printf("NUMBER %d\n", ft_printf("%05d", -42));
	printf("NUMBER %d\n", printf("%0+5d", -42));
	printf("NUMBER %d\n", ft_printf("%0+5d", -42));

	printf("NUMBER %d\n", printf("%+10.5d", 4242));
	printf("NUMBER %d\n", ft_printf("%+10.5d", 4242));
	printf("NUMBER %d\n", printf("%0+5d", 42));
	printf("NUMBER %d\n", ft_printf("%0+5d", 42));

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

	printf("NUMBER %d\n", ft_printf("%lu", 4294967295));
	printf("NUMBER %d\n", printf("%lu", 4294967296));
	printf("NUMBER %d\n", ft_printf("%lu", 4294967296));

	printf("NUMBER %d\n", printf("%llu", 4999999999));
	printf("NUMBER %d\n", ft_printf("%llu", 4999999999));
	printf("NUMBER %d\n", printf("%ju", 4999999999));
	printf("NUMBER %d\n", ft_printf("%ju", 4999999999));
	printf("NUMBER %d\n", printf("%ju", 4294967296));
	printf("NUMBER %d\n", ft_printf("%ju", 4294967296));
	printf("NUMBER %d\n", printf("%U", 4294967295));
	printf("NUMBER %d\n", ft_printf("%U", 4294967295));*/


	//printf("NUMBER %d\n", printf("% -3.5o", 9876543));
	//printf("NUMBER %d\n", ft_printf("% -3.5o", 9876543));
	/*char *str;
	printf ("real   %x eretr\n", 155);
	ft_printf ("custom %x eretr\n", 155);
	printf ("real   %hp eretr\n", &str);
	ft_printf ("custom %hp eretr\n", &str);*/

	//moulitests
	//int i;
	//printf("NUMBER %d\n", printf("%p", &i));
	//printf("NUMBER %d\n", ft_printf("%p", &i));
	/*printf("NUMBER %d\n", printf("% Zoooo"));
	printf("NUMBER %d\n", ft_printf("% Zoooo"));

	printf("NUMBER %d\n", printf("%D", -1L));
	printf("NUMBER %d\n", ft_printf("%D", -1L));*/

	//printf("NUMBER %d\n", printf("%o%o%o%o%o", 1, 100, 999, 42, 999988888));
	//printf("NUMBER %d\n", ft_printf("%o%o%o%o%o",	1, 100, 999, 42, 999988888));
	//printf("NUMBER %d\n", printf("%o", 999988888));
	//printf("NUMBER %d\n", ft_printf("%o",	999988888));
	//printf("NUMBER %d\n", printf("|%30O|", 9223372036854775807));
	//printf("NUMBER %d\n", ft_printf("|%30O|",	9223372036854775807));

	/*printf("NUMBER %d\n", printf("|%U|", 18446744073709551615));
	printf("NUMBER %d\n", ft_printf("|%U|",	18446744073709551615));*/
	/*
	printf("NUMBER %d\n", printf("|%U|", 18446744073709551615 / 2));
	printf("NUMBER %d\n", ft_printf("|%U|",	18446744073709551615 / 2));
	printf("NUMBER %d\n", printf("{% 03d}", 0));
	printf("NUMBER %d\n", ft_printf("{% 03d}", 0));
	printf("NUMBER %d\n", printf("%hD, %hD", 0, 65535));
	printf("NUMBER %d\n", ft_printf("%hD, %hD", 0, 65535));
	printf("NUMBER %d\n", printf("%hhO, %hhO", 0, 65535));
	printf("NUMBER %d\n", ft_printf("%hhO, %hhO", 0, 65535));
	printf("NUMBER %d\n", printf("%#o", 0));
	printf("NUMBER %d\n", ft_printf("%#o", 0));

	printf("NUMBER %d\n", printf("%-#.o, %#.0o", 0, 0));
	printf("NUMBER %d\n", ft_printf("%-#.o, %#.0o", 0, 0));

	printf("NUMBER %d\n", printf("%-#.O", 0));
	printf("NUMBER %d\n", ft_printf("%-#.O", 0));
	printf("NUMBER %d\n", printf("{% S}", NULL));
	printf("NUMBER %d\n", ft_printf("{% S}", NULL));
	printf("NUMBER %d\n", printf("%.u, %.0u", 0, 0));
	printf("NUMBER %d\n", ft_printf("%.u, %.0u", 0, 0));
	printf("NUMBER %d\n", printf("%4.s", "42"));
	printf("NUMBER %d\n", ft_printf("%4.s", "42"));
	printf("NUMBER %d\n", printf("{%05.s}", 0));
	printf("NUMBER %d\n", ft_printf("{%05.s}", 0));
	printf("NUMBER %d\n", printf("%.5p", 0));
	printf("NUMBER %d\n", ft_printf("%.5p", 0));
	printf("NUMBER %d\n", printf("{%-10Rt}"));
	printf("NUMBER %d\n", ft_printf("{%-10Rt}"));

	printf("NUMBER %d\n", printf("{%-05.Zt}"));
	printf("NUMBER %d\n", ft_printf("{%-05.Zt}"));

	printf("NUMBER %d\n", printf("{%-15Z}", 123));
	printf("NUMBER %d\n", ft_printf("{%-15Z}", 123));
	printf("NUMBER %d\n", printf("{%-*5d}", 2, 6));
	printf("NUMBER %d\n", ft_printf("{%-*5d}", 2, 6));
	printf("NUMBER %d\n", printf("{%#.5x}", 1));
	printf("NUMBER %d\n", ft_printf("{%#.5x}", 1));

	printf("NUMBER %d\n", printf("%#08x", 42));
	printf("NUMBER %d\n", ft_printf("%#08x", 42));
	printf("NUMBER %d\n", printf("{%3*d}", 2, 1));
	printf("NUMBER %d\n", ft_printf("{%3*d}", 2, 1));

	printf("NUMBER %d\n", printf("{%3*p}", 10, 5));
	printf("NUMBER %d\n", ft_printf("{%3*p}", 10, 5));
	printf("NUMBER %d\n", printf("{%*3d}", 5, 0));
	printf("NUMBER %d\n", ft_printf("{%*3d}", 5, 0));
	printf("NUMBER %d\n", printf("%lld", -9223372036854775808));
  printf("NUMBER %d\n", ft_printf("%lld", -9223372036854775808));

	printf("NUMBER %d\n", printf("%jd", -9223372036854775808));
  printf("NUMBER %d\n", ft_printf("%jd", -9223372036854775808));
	*/

	//MOULITESTS

	/*printf("NUMBER %d\n", printf("%ld", -9223372036854775808));
	printf("NUMBER %d\n", ft_printf("%ld", -9223372036854775808));
	printf("NUMBER %d\n", printf("%lld", -9223372036854775808));
	printf("NUMBER %d\n", ft_printf("%lld", -9223372036854775808));
	printf("NUMBER %d\n", printf("%jd", -9223372036854775808));
	printf("NUMBER %d\n", ft_printf("%jd", -9223372036854775808));
	printf("NUMBER %d\n", printf("%lld", -9223372036854775808));
	printf("NUMBER %d\n", ft_printf("%lld", -9223372036854775808));
	printf("NUMBER %d\n", printf("%jd", -9223372036854775808));
	printf("NUMBER %d\n", ft_printf("%jd", -9223372036854775808));

	printf("NUMBER %d\n", printf("%O", -9223372036854775806));
	printf("NUMBER %d\n", ft_printf("%O", -9223372036854775806));
	printf("NUMBER %d\n", printf("%zo, %zo", 0, 18446744073709551615));
	printf("NUMBER %d\n", ft_printf("%zo, %zo", 0, 18446744073709551615));

	printf("NUMBER %d\n", printf("%zi", -9223372036854775807));
	printf("NUMBER %d\n", ft_printf("%zi", -9223372036854775807));
	*/

	/*printf("NUMBER %d\n", printf("{%S}", NULL));
	printf("NUMBER %d\n", ft_printf("{%S}", NULL));

	printf("NUMBER %d\n", printf("{%05.S}", L"42 c est cool"));
	printf("NUMBER %d\n", ft_printf("{%05.S}", L"42 c est cool"));*/
  //* больше потом число - число
	//* меньше потом число - число
	//число больше * - число
	//число меньше * - звезда

	/*printf("NUMBER %d\n", printf("%o", 40));
  printf("NUMBER %d\n", ft_printf("%o", 40));*/

	/*printf("NUMBER %d\n", printf("%lu", -42));
  printf("NUMBER %d\n", ft_printf("%lu", -42));
	printf("NUMBER %d\n", printf("%U", 9223372036854775808));
  printf("NUMBER %d\n", ft_printf("%U", 9223372036854775808));
	printf("NUMBER %d\n", printf("%lu, %lu", 0, 9223372036854775808));
  printf("NUMBER %d\n", ft_printf("%lu, %lu", 0, 9223372036854775808));
	printf("NUMBER %d\n", printf("%llu, %llu", 0, 18446744073709551615));
  printf("NUMBER %d\n", ft_printf("%llu, %llu", 0, 18446744073709551615));
	printf("NUMBER %d\n", printf("%ju, %ju", 0, 18446744073709551615));
  printf("NUMBER %d\n", ft_printf("%ju, %ju", 0, 18446744073709551615));
	printf("NUMBER %d\n", printf("%zu, %zu", 0, 18446744073709551615));
  printf("NUMBER %d\n", ft_printf("%zu, %zu", 0, 18446744073709551615));*/

	/*printf("NUMBER %d\n", printf("%hhhllzlhjlu", 1178955456));
	printf("NUMBER %d\n", ft_printf("%hhhllzjlhlu",1178955456));*/
	//int d;
	//int f;
	//printf("NUMBER %d\n", printf("real   %%%010.20ls dsfdsfdsf %c %+d %+i %u %S|%n", L"string", 'c', 156, 651, 54646, L"abcdef", &d));
	//printf("NUMBER %d\n", ft_printf("real   %010.20ls dsfdsfdsf %c %+d %+i %u %S|%n", L"string", 'c', 156, 651, 54646, L"abcdef", &f));
	//printf("%010.20s\n", "string");
	//ft_printf("%010.20s\n", "string");

	//printf("NUMBER %d\n", printf("%lu %n", -42, &d));
  //printf("NUMBER %d\n", ft_printf("%lu %n", -42, &f));
	//ft_printf("%c\n", 'c');
	//ft_printf("%+d\n", 156);
	//ft_printf("%+i\n", 651);
	//ft_printf("%u\n", 54646);
	//ft_printf("%S\n", L"abcdef");*/

	/*printf("%d\n", d);
	printf("%d\n", f);*/
	/*printf("NUMBER %d\n", printf("%S", L"з±≥"));
  printf("NUMBER %d\n", ft_printf("%S", L"з±≥"));
	printf("NUMBER %d\n", printf("{%30S}", L"жM-M-^QжM-^XѓдЄM-еM-^O™зM-^LЂгM-M-^B"));
  printf("NUMBER %d\n", ft_printf("{%30S}", L"жM-M-^QжM-^XѓдЄM-еM-^O™зM-^LЂгM-M-^B"));
	printf("NUMBER %d\n", printf("{%030S}", L"жM-M-^QжM-^XѓдЄM-еM-^O™зM-^LЂгM-M-^B"));
  printf("NUMBER %d\n", ft_printf("{%030S}", L"жM-M-^QжM-^XѓдЄM-еM-^O™зM-^LЂгM-M-^B"));
	printf("NUMBER %d\n", printf("%.4S", L"жM-M-^QжM-^XѓдЄM-еM-^O™зM-^LЂгM-M-^B"));
  printf("NUMBER %d\n", ft_printf("%.4S", L"жM-M-^QжM-^XѓдЄM-еM-^O™зM-^LЂгM-M-^B"));*/
	//printf("NUMBER %d\n", printf("%S", L"з±≥"));*/
  //printf("NUMBER %d\n", ft_printf("%S", L"з±≥"));
	/*printf("NUMBER %d\n", printf("%S", L"米"));
  printf("NUMBER %d\n", ft_printf("%S", L"米"));
	printf("NUMBER %d\n", printf("{%30S}", L"我是一只猫。"));
  printf("NUMBER %d\n", ft_printf("{%30S}", L"我是一只猫。"));
	printf("NUMBER %d\n", printf("{%030S}", L"我是一只猫。"));
  printf("NUMBER %d\n", ft_printf("{%030S}", L"我是一只猫。"));
	printf("NUMBER %d\n", printf("%.4S", L"我是一只猫。"));
  printf("NUMBER %d\n", ft_printf("%.4S", L"我是一只猫。"));*/


	/*printf("NUMBER %d\n", printf("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير"));
  printf("NUMBER %d\n", ft_printf("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير"));
	printf("NUMBER %d\n", printf("%lc, %lc", L'暖', L'ح'));
  printf("NUMBER %d\n", ft_printf("%lc, %lc", L'暖', L'ح'));
	printf("NUMBER %d\n", printf("%hhC, %hhC", 0, L'米'));
  printf("NUMBER %d\n", ft_printf("%hhC, %hhC", 0, L'米'));
	printf("NUMBER %d\n", printf("%.4S", L"我是一只猫。"));
  printf("NUMBER %d\n", ft_printf("%.4S", L"我是一只猫。"));

	printf("NUMBER %d\n", printf("%C", L'猫'));
  printf("NUMBER %d\n", ft_printf("%C", L'猫'));
	printf("NUMBER %d\n", printf("{% C}", 0));
  printf("NUMBER %d\n", ft_printf("{% C}", 0));*/




//}
