/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:26:19 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/22 16:26:23 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>

void	argument_analize(t_argc *params, va_list ap)
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
		if (n_value)
			*n_value = (*params).res;
	}
}

void	check_star_anywhere(char c, int *i, int *param)
{
	if (c == '*')
	{
		*param = '*';
		(*i)++;
	}
}

void	argument_save(char *argv, t_argc *params, va_list ap)
{
	int i;
	int j;

	i = 0;
	j = 0;
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
	precision_finder(argv, &i, params);
	check_star_anywhere(argv[i], &i, &params->width);
	check_length(&argv[i], &i, (*params).length);
	check_star_anywhere(argv[i], &i, &params->width);
	specifier_finder(params, argv, &i, ap);
	if (!(*params).left)
		while (argv[i])
		{
			write(1, &argv[i++], 1);
			(*params).res++;
		}
}

void	struct_init(t_argc *params)
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
	ft_strdel(&params->left);
	ft_strdel(&params->one_arg);
}

int		ft_printf(const char *format, ...)
{
	int				i;
	va_list		ap;
	t_argc		params;

	i = 0;
	params.res = 0;
	va_start(ap, format);
	while (format[i] && format[i] != '%')
	{
		write(1, &format[i++], 1);
		params.res++;
	}
	while (format[i])
	{
		if (format[i] == '%' && !if_percent_found(format, &params, &i))
			continue;
		else
			while (format[i] && format[i] != '%')
			{
				write(1, &format[i++], 1);
				params.res++;
			}
		if (params.one_arg)
			argument_save(params.one_arg, &params, ap);
	}
	va_end(ap);
	return (params.res);
}

/*int		main(void)
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

	/*printf("NUMBER %d\n", printf("|%0#5llo|", 0));
  printf("NUMBER %d\n", ft_printf("|%0#5llo|", 0));
	printf("NUMBER %d\n", printf("|%#.4o|", 0));
  printf("NUMBER %d\n", ft_printf("|%#.4o|", 0));
	printf("NUMBER %d\n", printf("|%#.4o|", 0));
  printf("NUMBER %d\n", ft_printf("|%#.4o|", 0));

	printf("NUMBER %d\n", printf("|%#.4o|", 0));
  printf("NUMBER %d\n", ft_printf("|%#.4o|", 0));
	printf("NUMBER %d\n", printf("%#o", 0));
  printf("NUMBER %d\n", ft_printf("%#o", 0));

	printf("NUMBER %d\n", printf("@moulitest: %#.o %#.0o", 0, 0));
  printf("NUMBER %d\n", ft_printf("@moulitest: %#.o %#.0o", 0, 0));
	printf("NUMBER %d\n", printf("%#.O", 0));
  printf("NUMBER %d\n", ft_printf("%#.O", 0));
	printf("NUMBER %d\n", printf("%#.o, %#.0o", 0, 0));
  printf("NUMBER %d\n", ft_printf("%#.o, %#.0o", 0, 0));


	printf("NUMBER %d\n", printf("|%#5.3o|", 25));
  printf("NUMBER %d\n", ft_printf("|%#5.3o|", 25));

	printf("NUMBER %d\n", printf("%#6o", 2500));
  printf("NUMBER %d\n", ft_printf("%#6o", 2500));
	printf("NUMBER %d\n", printf("%-#6o", 2500));
  printf("NUMBER %d\n", ft_printf("%-#6o", 2500));*/
	//printf("NUMBER %d\n", printf("%lu", -42));
  //printf("NUMBER %d\n", ft_printf("%lu", -42));
	/*printf("NUMBER %d\n", printf("%lu", -42));
  printf("NUMBER %d\n", ft_printf("%lu", -42));
	printf("NUMBER %d\n", printf("%lu", -42));
  printf("NUMBER %d\n", ft_printf("%lu", -42));
	printf("NUMBER %d\n", printf("%lu", -42));
  printf("NUMBER %d\n", ft_printf("%lu", -42));*/
//}
