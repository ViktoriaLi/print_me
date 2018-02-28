#include <stdio.h>
#include <stddef.h>
#include <locale.h>
#include <limits.h>
#include <errno.h>
#include "ft_printf.h"

#define CNV "X"
int		main(void)
{
  int nmb = 4235;

	setlocale (LC_ALL, "");
  const wchar_t B[] = L"ድመቶች ሰዎች አልወደውም.";
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

	/*printf("NUMBER %d\n", printf("|%05.1d|", 25));
  printf("NUMBER %d\n", ft_printf("|%05.1d|", 25));

	printf("NUMBER %d\n", printf("|%05.0d|", 25));
  printf("NUMBER %d\n", ft_printf("|%05.0d|", 25));

	printf("NUMBER %d\n", printf("%03.3d", -1));
  printf("NUMBER %d\n", ft_printf("%03.3d", -1));
	//printf("NUMBER %d\n", printf("%#08x", 42));
  //printf("NUMBER %d\n", ft_printf("%#08x", 42));*/

	/*printf("NUMBER %d\n", printf("%f", 5.1234567));
  printf("NUMBER %d\n", ft_printf("%f", 5.1234567));
	printf("NUMBER %d\n", printf("%f", 5.1234561));
  printf("NUMBER %d\n", ft_printf("%f", 5.1234561));
	printf("NUMBER %d\n", printf("%f", 5.123456));
  printf("NUMBER %d\n", ft_printf("%f", 5.123456));
	printf("NUMBER %d\n", printf("%f", 5.12));
  printf("NUMBER %d\n", ft_printf("%f", 5.12));
	printf("NUMBER %d\n", printf("% f", 5.1234567));
  printf("NUMBER %d\n", ft_printf("% f", 5.1234567));
	printf("NUMBER %d\n", printf("%-20f", 5.1234567));
  printf("NUMBER %d\n", ft_printf("%-20f", 5.1234567));
	printf("NUMBER %d\n", printf("%20f", 5.1234567));
  printf("NUMBER %d\n", ft_printf("%20f", 5.1234567));

	printf("NUMBER %d\n", printf("%f", 5));
  printf("NUMBER %d\n", ft_printf("%f", 5));*/


	/*printf("NUMBER %d\n", printf("%20.10f", 5.1234567));
  printf("NUMBER %d\n", ft_printf("%20.10f", 5.1234567));
	printf("NUMBER %d\n", printf("%-20.10f", 5.1234567));
  printf("NUMBER %d\n", ft_printf("%-20.10f", 5.1234567));
	printf("NUMBER %d\n", printf("{%f}{%F}", 1.42, 1.42));
	printf("NUMBER %d\n", ft_printf("{%f}{%F}", 1.42, 1.42));*/
	//printf("NUMBER %d\n", printf("%20.100f", 5.12345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910));
	//printf("NUMBER %d\n", ft_printf("%20.100f", 5.12345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910));
	/*printf("NUMBER %d\n", printf("|%05.1d|", 25)); //<=
  printf("NUMBER %d\n", ft_printf("|%05.1d|", 25));
	printf("NUMBER %d\n", printf("%03.2d", -1)); //!=
  printf("NUMBER %d\n", ft_printf("%03.2d", -1));*/
	/*int k = 0;

	printf("NUMBER %d\n", printf("|%5.4td|%n", -25, &k));
  printf("NUMBER %d\n", ft_printf("|%5.4td|%n", -25, &k));*/

	/*printf("NUMBER %d\n", printf("|%lc|", 0));
  printf("NUMBER %d\n", ft_printf("|%lc|", 0));
	printf("NUMBER %d\n", printf("|%C|", 0));
  printf("NUMBER %d\n", ft_printf("|%C|", 0));
	printf("NUMBER %d\n", printf("|%lc|", 0));
  printf("NUMBER %d\n", ft_printf("|%lc|", 0));
	printf("NUMBER %d\n", printf("|%lc|", 0));
  printf("NUMBER %d\n", ft_printf("|%lc|", 0));
	printf("NUMBER %d\n", printf("|%lc|", 0));
  printf("NUMBER %d\n", ft_printf("|%lc|", 0));*/


	/*Fail test_b020.c[#0007]: printf("|%5.4Ld|%n", -25, &k);   printf("%d|", k); k = 0;
	Your str : "|    %Ld|"
	Corr str : "|-0025|7|"
	Your ret : ""
	Corr ret : ""
	Extra code: ]
	*/
	//printf("NUMBER %d\n", printf("|%0-5.3d|", -25));
  //printf("NUMBER %d\n", ft_printf("|%0-5.3d|", -25));

	/*printf("NUMBER %d\n", printf("{%03.4d}", 0));
  printf("NUMBER %d\n", ft_printf("{%03.4d}", 0));
	printf("NUMBER %d\n", printf("{%03.4d}", 1));
  printf("NUMBER %d\n", ft_printf("{%03.4d}", 1));*/

  printf("1NUMBER %d\n", printf("|%-3w|(%3w)\t|%3Z|(%3Z)\t|%Q|(%3Q)"));
  printf("2NUMBER %d\n", ft_printf("|%-3w|(%3w)\t|%3Z|(%3Z)\t|%Q|(%3Q)"));
  printf("3NUMBER %d\n", printf("|%3h|\t|%3l|\t|%3hhll|\t|%3llhhllQ|\t|%3z|\t|%3j|\t|%3J|"));
  printf("4NUMBER %d\n", ft_printf("|%3h|\t|%3l|\t|%3hhll|\t|%3llhhllQ|\t|%3z|\t|%3j|\t|%3J|"));
  printf("5NUMBER %d\n", printf("|%-6%|   |%6%|   |%6.2%|   |%-06%|   |%-06.3%|"));
  printf("6NUMBER %d\n", ft_printf("|%-6%|   |%6%|   |%6.2%|   |%-06%|   |%-06.3%|"));
  /*printf("19NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("20NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("21NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("22NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("23NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("24NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("25NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("26NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("31NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("32NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("33NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("34NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("35NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("36NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("37NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("38NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("39NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("40NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("41NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("42NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("43NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("44NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("45NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("46NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("47NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("48NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("49NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("50NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("51NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("52NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("53NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("54NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("55NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("56NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("57NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("58NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("59NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("60NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("61NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("62NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("63NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("64NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("65NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("66NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("67NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("68NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("69NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("70NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("71NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("72NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("73NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("74NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("75NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("76NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("77NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("78NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("79NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("80NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("81NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("82NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("83NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("84NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("85NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("86NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("87NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("88NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("89NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("90NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("91NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("92NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("93NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("94NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("95NUMBER %d\n", printf("|d/D|\t|%22zd|\t|%22zD|\t|%22jd|\t|%22jD|", -9223372036854775808,-9223372036854775808,-9223372036854775808,-9223372036854775808));
  printf("96NUMBER %d\n", ft_printf("|d/D|\t|%22zd|\t|%22zD|\t|%22jd|\t|%22jD|", -9223372036854775808,-9223372036854775808,-9223372036854775808,-9223372036854775808));
  printf("97NUMBER %d\n", printf("|d/D|\t|%22lld|\t|%22llD|\t|%22hhd|\t|%22hhD|", -9223372036854775808,-9223372036854775808,-9223372036854775808,-9223372036854775808));
  printf("98NUMBER %d\n", ft_printf("|d/D|\t|%22lld|\t|%22llD|\t|%22hhd|\t|%22hhD|", -9223372036854775808,-9223372036854775808,-9223372036854775808,-9223372036854775808));
  printf("99NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("100NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("101NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("102NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("103NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("104NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("105NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("106NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("107NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("108NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("109NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("110NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("111NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("112NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("113NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("114NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("115NUMBER %d\n", printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("116NUMBER %d\n", ft_printf("|%5h h"CNV"|\t|%20l l"CNV"|", -32767,-2147483647));
  printf("117NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("118NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("119NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("120NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("121NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("122NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("123NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("124NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("125NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("126NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("127NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("128NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("129NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("130NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("131NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("132NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("135NUMBER %d\n", printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));
  printf("136NUMBER %d\n", ft_printf("|%-#13.10"CNV"|\t|%-12#.10"CNV"|\t|%-13.10#"CNV"|\t|%-13.-9#"CNV"|\t\t", 25,25,25,25));*/
}
