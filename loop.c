# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

char	*print_hex(int nbr, unsigned int base, int count)
{
	char		*res;
	int		i;
	int len;
	int d;

	d = nbr;
	len = 1;
	i = 0;
	res = NULL;

	while (d > base - 1)
	{
		d = d / base;
		len++;
	}
	if (!(res = (char *)malloc((len + 1))))
		return (NULL);
	res[len--] = 0;
	while (len >= 0)
	{
		if ((nbr % base) < 10)
			res[len--] = (nbr % base) + 48;
		else if (base == 16)
			res[len--] = (nbr % base) - 10 + 97;
		nbr = nbr / base;
	}

	//res[i] = 0;

	/*while (nbr >= base)
	{
		if ((nbr % base) < 10)
			res[i++] = (nbr % base) - 10 + 97;
		nbr /= base;
	}*/
	return (res);
}

/*dest = NULL;
len = 1;
d = n;
while (d > 9)
{
	d = d / 10;
	len++;
}
if (!(dest = (char *)malloc((len + 1))))
	return (NULL);
dest[len--] = 0;
while (len >= 0)
{
	dest[len--] = n % 10 + '0';
	n = n / 10;
}
return (dest);*/

int main()
{
	printf("%s\n", print_hex(6523, 8, 20));
}
