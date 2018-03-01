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

	кейс printf("NUMBER %d\n", printf("% +-0#10.5ls", "test")); возвращает -1
	кейс printf("NUMBER %d\n", printf("% -20d", 0)); должен быть пробел
	кейс printf("NUMBER %d\n", printf("% -20d", 0)); - не выводит число, только пробелы
	если нет точности, но есть флаг 0 - сделать вывод нолей
	ошибка на %-5.1s
	проверить что на  выводит printf("NUMBER %d\n", printf("@moulitest: %c", 0));
	*/

    printf("NUMBER %d\n", printf("@moulitest: %c", 0));
    printf("NUMBER %d\n", ft_printf("@moulitest: %c", 0));
    printf("NUMBER %d\n", printf("% -20d", 0));
    printf("NUMBER %d\n", ft_printf("% -20d", 0));
    printf("NUMBER %d\n", printf("% -20.d", 2147483648));
    printf("NUMBER %d\n", ft_printf("% -20.d", 2147483648));
    printf("NUMBER %d\n", printf("% +0-5.15d", -2147483648));
    printf("NUMBER %d\n", ft_printf("% +-05.15d", -2147483648));
  	printf("NUMBER %d\n", printf("% -20.d", 0));
  	printf("NUMBER %d\n", ft_printf("% -20.d", 0));
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
    printf("custom %%%s dsfdsfdsf %c %+lld %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");
  	ft_printf("custom %%%s dsfdsfdsf %c %+lld %+i %u %S\n", "string", 'c', 156, 651, 54646, L"abcdef");
  	printf ("real   %U eretr\n", 123);
  	ft_printf ("custom %U eretr\n", 123);
  	printf ("real   %10x eretr\n", 1422);
  	ft_printf ("custom %10x eretr\n", 1422);



  /* unitforum checker
  printf("1NUMBER %d\n", printf("|%-3w|(%3w)\t|%3Z|(%3Z)\t|%Q|(%3Q)"));
  printf("2NUMBER %d\n", ft_printf("|%-3w|(%3w)\t|%3Z|(%3Z)\t|%Q|(%3Q)"));
  printf("3NUMBER %d\n", printf("|%3h|\t|%3l|\t|%3hhll|\t|%3llhhllQ|\t|%3z|\t|%3j|\t|%3J|"));
  printf("4NUMBER %d\n", ft_printf("|%3h|\t|%3l|\t|%3hhll|\t|%3llhhllQ|\t|%3z|\t|%3j|\t|%3J|"));
  printf("5NUMBER %d\n", printf("|%-6%|   |%6%|   |%6.2%|   |%-06%|   |%-06.3%|"));
  printf("6NUMBER %d\n", ft_printf("|%-6%|   |%6%|   |%6.2%|   |%-06%|   |%-06.3%|"));
  printf("19NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("20NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("31NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("32NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("39NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("40NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("47NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("48NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("55NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("56NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("63NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("64NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("71NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("72NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("79NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("80NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("87NUMBER %d\n", printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("88NUMBER %d\n", ft_printf("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42));
  printf("21NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("22NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("25NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("26NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("33NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("34NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("41NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("42NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("49NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("50NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("57NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("58NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("65NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("66NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("73NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("74NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("81NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("82NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("89NUMBER %d\n", printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("90NUMBER %d\n", ft_printf("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42));
  printf("23NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("24NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("35NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("36NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("37NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("38NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("43NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("44NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("45NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("46NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("51NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("52NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("53NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("54NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("59NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("60NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("61NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("62NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("67NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("68NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("69NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("70NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("75NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("76NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("77NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("78NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("83NUMBER %d\n", printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("84NUMBER %d\n", ft_printf("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42));
  printf("85NUMBER %d\n", printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
  printf("86NUMBER %d\n", ft_printf("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42));
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
