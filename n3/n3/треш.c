#include <stdio.h>
#include <math.h>
#include <locale.h>

//const double PI = 3.14159265358979323846;
void main()
{
   setlocale(LC_ALL, "Russian");
   int numb, k;
   printf("задайте точность вычисления числа пи и до какого числа хотите его посчитать:");
   scanf_s("%d%d", &numb, &k);
   double acc = 1.0/pow(10, numb);
   double row = 0.0, sgn = 1.0, S;
   int n;
   do {
	   S = 1.0 / (2.0 * n - 1);
		row += S * sgn;
	   sgn *= (-1.0);
	   n++;
   } while (S >= row);
   printf("pi=%.*f\n", k, row * 4.0);
}