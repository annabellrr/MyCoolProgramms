#include <stdio.h>
#include <math.h>
#include <float.h>
#include <locale.h>

double f(double x)
{
    return sin(x);
}

double trap(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2;
    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}

double inacc(double n, double a, double b)
{
    return pow(n, 2) * (b - a) / 12 * fabs(6 * b);
}

void main()
{
    setlocale(LC_ALL, "Russian");
    double a, b;
    int n;
    printf("введите А = ");
    scanf_s("%lf", &a);
    printf("введите B = ");
    scanf_s("%lf", &b);
    printf("введите n = ");
    scanf_s("%d", &n);
    double res = trap(a, b, n);
    printf("\nинтегришка sin(x) от %lf до %lf = %lf \t", a, b, res);
    double eps = inacc(a, b, n);
    printf("\n точность = %lf", eps);
}
