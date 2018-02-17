#include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <locale.h>
# include <wchar.h>

#include "ft_printf.h"

char *print_hex_ind(uintmax_t nbr, unsigned int base, int count)
{
	static char *res;
	static int i;

	i = 0;
	res = NULL;
	res = (char *)malloc(count + 1);
	while (i < count)
		res[i++] = 0;
	i = 0;
	if (nbr >= base)
		print_hex_ind(nbr / base, base, count);
	if ((nbr % base) < 10)
		res[i++] = (nbr % base) + 48;
	else
		res[i++] = (nbr % base) - 10 + 65;
	return (res);
}

/*int main()
{
	int i = 0;
	int j;
	j = 0;
	wchar_t test;
	test = L'®';
	unsigned int code = (unsigned int)L'®';
	printf("CODE %d\n", code);
	char *hex_code;
	hex_code = NULL;
	hex_code = print_hex_ind(code, 16, 16);
	printf("HEX_CODE %s\n", hex_code);
	int len = ft_strlen(hex_code);
	char tmp[5];
	//tmp = NULL;
	while (i < 4)
	{
		tmp[i] = '0';
		i++;
	}
	i--;
	j = len - 1;
	printf("CODE %d\n", j);
	if (len < 4)
	{
		while(j >= 0)
		{
			tmp[i] = hex_code[j];
			i--;
			j--;
		}
	}
	printf("HEX_CODE %s\n", tmp);
	int k = 0;
	int l = 0;
	char be_code[4][5]
	while (k < 4)
	{
		l = 0;
			while (l < 5)
			{
				be_code[k][l] = '0';
				l++;
			}
		k++;
	}
	k = 0;
	char *tmp2;
	while (k < 4)
	{

	}
	char *code_2 = print_hex_ind(code, 2, 20);
	printf("HEX_CODE %s\n", code_2);*/
	/*const double RENT = 3852.99;
	printf("*%8f*\n", RENT);
	printf("*%e*\n", RENT);
	printf("*%4.2f*\n", RENT);
	printf("*%3.1f*\n", RENT);
	printf("*%10.3f*\n", RENT);
	printf("*%10.3E*\n", RENT);
	printf("*%+4.2f*\n", RENT);

	printf("%x %X %#x\n", 31, 31, 31);
	printf("**%d**% d% d **\n", 42, 42, -42);
	printf("**%5d**%5.3d**%05d**%05.3d**\n", 6, 6, 6, 6);
	printf("\n");

	printf("[%2s]\n", BLURB);
	printf("[%24s]\n", BLURB);
	printf("[%24.5s]\n", BLURB);
	printf("[%-24.5s]\n", BLURB);*/

	/*printf ("%6d\n%6d\n%6d\n",123,42,1523);
	printf ("%-6d\n%-6d\n%-6d\n",123,42,1523);
	printf ("%6d\n", 123);
	printf ("%o\n",123);
	short int d1 = 123;
	printf ("%+10.6hderetr%d\n", d1);
	printf ("%lggfhfhfgh\n",123);*/
	//printf ("%LS\n", "123");

//}

int main(void)
{
	//setlocale (LC_ALL, "");
	int i;
	int j;
	int bytes_count;
	int code;
	char res[5];
	i = 0;
	j = 0;
	code = 0;
	bytes_count = 0;
	wchar_t *test;
	test = L"а";
	while (i < 5)
	{
		res[i] = 0;
		i++;
	}
	i = 0;
	//res = (wchar_t *)malloc(sizeof(wchar_t) * 20);
	//res = NULL;

	//printf("%s %s \n", print_hex_ind(test[0], 2, 20), print_hex_ind(test[1], 2, 20));
	//printf("%s %s \n", print_hex_ind(test[0] >> 5, 2, 20), print_hex_ind(test[1], 2, 20));
	while (test[i] != 0)
	{
		if (test[i] <= 127)
		{
			write(1, &test[i], 1);
		}
		else
		{
			while (i < 5)
			{
				res[i] = 0;
				i++;
			}
			bytes_count = 0;
			if (test[i] > 127 && test[i] <= 2047)
			{
				bytes_count = 2;
				res[0] = test[i] >> 6;
				res[0] = res[0] & 31;
				res[0] += 192;
				i++;
				res[1] = res[1] & 63;
				res[1] += 128;
				write(1, res, bytes_count);
			}
			else if (test[i] > 2047 && test[i] <= 65535)
			{
				bytes_count = 3;
				res[0] = test[i] >> 12;
				res[0] = res[0] & 15;
				res[0] += 224;
				i++;
				res[1] = test[i] >> 6;
				res[1] = res[1] & 63;
				res[1] += 128;
				i++;
				res[2] = res[2] & 63;
				res[2] += 128;
				write(1, res, bytes_count);
			}
			else if (test[i] > 65535 && test[i] <= 1114111)
			{
				bytes_count = 4;
				res[0] = test[i] >> 18;
				res[0] = res[0] & 7;
				res[0] += 240;
				i++;
				res[1] = test[i] >> 12;
				res[1] = res[1] & 63;
				res[1] += 128;
				i++;
				res[2] = test[i] >> 6;
				res[2] = res[2] & 63;
				res[2] += 128;
				i++;
				res[3] = res[2] & 63;
				res[3] += 128;
				write(1, res, bytes_count);
			}
			printf("BYTE %d\n", bytes_count);
		}
		i++;
		j++;
	}

	//test[0] = test[0] >> 5;
	//printf("%d \n", test[0]);
	/*while (test[i] != 0)
	{
		bytes_count = 0;
		if (test[i] <= 127)
			res[j] = test[i];
		else
		{
			if (test[i] >> 5 == 11)
				bytes_count = 2;
			else if (test[i] >> 4 == 111)
				bytes_count = 3;
			else if (test[i] >> 3 == 1111)
				bytes_count = 4;
			if (bytes_count == 2)
				res[j] &= 11111;
			else if (bytes_count == 3)
				res[j] &= 1111;
			else if (bytes_count == 4)
				res[j] &= 111;
			bytes_count--;
			i++;
			while (bytes_count > 0)
			{
				printf("code %d", res[j]);
				res[j] <<= 6;
				res[j] |= test[i];
				i++;
				bytes_count--;
			}
		}
		j++;
	}*/
	//printf("S\n", res);
	//write(1, &test, 1);
	//write(1, &t, 1);
	//write(1, "\n", 1);
}
