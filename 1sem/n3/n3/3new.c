#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	//без свич кейса, с выводом со звездочкой
	printf("Эта программа выводит число Pi с заданной точностью до определенного знака\nВведите число до которого\
 хотите посчитать число Pi\n");
	int i, numb = 0, n = 0;
	double count = 1, S1 = 0, S2 = 0;
	int s = scanf_s("%d", &numb);
	if ((numb < 0) || (s < 1)) {
		printf("Вы ввели неправильный тип переменной");
		return (90);
	}
	for (i = 1; i <= numb; i++) { /*мы высчитываем точность до которой
		 хотим посчитать число Pi*/
		count /= 10;
	}
	do {
		n++;
		S1 = S2 + (4.0 / (2 * n - 1));
		n++;
		S2 = S1 - (4.0 / (2 * n - 1));
	} while ((S1 - S2) > count);
	printf("%.*f\n", numb, (float)((S1 + S2) / 2));
	}
	printf("%d", n);
	int c;
	scanf_s("%d", &c);
	return 0;
}





int N;
printf("Введите точность вычисления:");
scanf_s("%d", &N);
int k;
printf("Введите необходимое количество знаков после запятой:");
scanf_s("%d", &k);
double row = 0.0;
double sgn = 1.0;
double acc = 1.0 / pow(10, N + 1);
int n = 0;
double S;
do
{
	S = 1.0 / (2.0 * n + 1);
	row += sgn * S;
	sgn *= (-1.0);
	++n;
} while (ser >= lim);
printf("Вычисленное число pi:%.*f\n", k, 4.0 * row);
printf("Количество членов в ряду:%i\n", n);
double diff = PI - 4.0 * sum;
printf("Погрешность вычисления: %.10E", diff);