#include <stdio.h>
#include <math.h>
#include <locale.h>
double f(double x)
{
	return sin(x);
}

double df(double x) {
	return cos(x);
}

void main()
{
	setlocale(LC_ALL, "Russian");
	double x, ac, xk, delta;
	int k = 0;
	printf("введите разбиение = ");
	scanf_s("%lf", &x);
	printf("введите точность = ");
	scanf_s("%lf", &ac);
	do
	{
		xk = (double)(x - f(x) / df(x));
		delta = (double)(fabs(xk - x));
		if (delta > ac)
		{
			x = xk;
			k++;
		}
	} while (delta <= ac);
	printf("xk = %lf\n", x);
}