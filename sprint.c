#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
unsigned long long a = 0;
unsigned long long b = 0;
unsigned long long i = 0;
unsigned long long res = 0;
unsigned long long m = pow(10, 9) + 7;
char *str1 = malloc(10000);
char *str2 = malloc(10000);;
scanf("%s", str1);
scanf("%s", str2);
int len1 = strlen(str1);
int len2 = strlen(str2);
while (str1[i] && --len1 >= 0)
{
  if (str1[i] == '1')
    a += pow(2, len1);
  i++;
}
i = 0;
while (str2[i] && --len2 >= 0)
{
  if (str2[i] == '1')
    b += pow(2, len2);
  i++;
}
i = 0;
while (i <= 314159)
{
  res += a^(b << i);
  i++;
}
printf("%s %s\n", str1, str2);
printf("%lld\n", m);
printf("%lld\n", a);
printf("%lld\n", b);
printf("%lld\n", res % m);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
unsigned long long a = 0;
unsigned long long b = 0;
unsigned long long i = 0;
unsigned long long res = 0;
unsigned long long m = pow(10, 9) + 7;
unsigned long long *a1 = malloc(sizeof(unsigned long long) * 314159);
unsigned long long *b1 = malloc(sizeof(unsigned long long) * 314159);

char *str1 = malloc(10000);
char *str2 = malloc(10000);;
scanf("%s", str1);
scanf("%s", str2);
int len1 = strlen(str1);
int len2 = strlen(str2);
while (str1[i] && --len1 >= 0)
{
  if (str1[i] == '1')
    a += pow(2, len1);
  i++;
}
i = 0;
while (str2[i] && --len2 >= 0)
{
  if (str2[i] == '1')
    b += pow(2, len2);
  i++;
}
i = 0;
while (i < 314159)
{
   a1[i] = a;
   i++;
}
i = 0;
while (i < 314159)
{
   b1[i] = b;
   i++;
}
i = 0;
while (i <= 314159)
{
  res += a^(b << i);
  i++;
}
printf("%lld\n", res % m);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
unsigned long long a = 0;
unsigned long long b = 0;
unsigned long long i = 0;
unsigned long long res = 0;
long m = pow(10, 9) + 7;
unsigned char *str1 = malloc(10000);
unsigned char *str2 = malloc(10000);;
scanf("%s", str1);
scanf("%s", str2);
unsigned long len1 = strlen(str1);
unsigned long len2 = strlen(str2);
while (str1[i] && --len1 >= 0)
{
  if (str1[i] == '1')
    a += pow(2, len1);
  i++;
}
i = 0;
while (str2[i] && --len2 >= 0)
{
  if (str2[i] == '1')
    b += pow(2, len2);
  i++;
}
i = 0;
while (i <= 314159)
{
  res = (res + a^(b << i))% m ;
  i++;
}
printf("%lld\n", res);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
long a = 0;
long b = 0;
long i = 0;
long res = 0;
long m = pow(10, 9) + 7;
char *str1 = malloc(10000);
char *str2 = malloc(10000);;
scanf("%s", str1);
scanf("%s", str2);
long len1 = strlen(str1);
long len2 = strlen(str2);
while (str1[i] && --len1 >= 0)
{
  if (str1[i] == '1')
    a += pow(2, len1);
  i++;
}
i = 0;
while (str2[i] && --len2 >= 0)
{
  if (str2[i] == '1')
    b += pow(2, len2);
  i++;
}
i = 0;
while (i <= 314159)
{
  res = (res + (a^(b << i)))% m ;
  i++;
}
printf("%ld\n", res % m);
    return 0;
}
