#include <stdio.h>
#include <math.h>
#include <locale.h>
int main(void)
{
	setlocale(LC_ALL, "Russian");
	int N, i = 1, k = 1;
	long double pi = 0, delta = 1, R;

	printf("введите число знака, до которого хотите вывести пишку:\n");
	scanf_s("%d", &N);

	R = pow(10, -(N+2));

	while (delta > R)
	{
		delta = (long double)4 / i;
		pi = pi + k * delta;
		i = i + 2;
		k = -k;
	}
	printf("%.*Lf\n", N, pi);
}

// const double PI = 3.14159265358979323846;