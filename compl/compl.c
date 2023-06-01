//от Лысакова

//решение задачки
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>


typedef struct Complex
{
    double real;
    double imag;
} Complex;

void complex_print(Complex numb)
{
    printf("%lf + %lfi\n", numb.real, numb.imag);
}

double complex_abs(Complex numb)
{
    return sqrt(numb.real * numb.real + numb.imag * numb.imag);
}

typedef struct array
{
    int size;
    double* pMas;
} array;

double compare(double x, double y)
{
    return x > y;
}

double replace(double* x, double* y)
{
    double temp = *x;
    *x = *y;
    *y = temp;
}

array init_array(int size)
{
    array res;
    res.size = size;
    res.pMas = malloc(size * sizeof(double));
    return res;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    FILE* fcomplex = fopen("chiselki.txt", "r");
        if (fcomplex == NULL)
            printf("Ошибка при открытии файла");

    array chiselki = init_array(10);
    for (int i = 0; i < chiselki.size; i++)
        fscanf(&fcomplex, "%lf", chiselki.pMas + i);

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9 - i; j++)
        {
            double a = complex_abs(&chiselki[i]);
            double b = complex_abs(&chiselki[i + 1]);
            if (compare(a, b))
                replace(&a, &b);
        }
    printf("%lf", chiselki);


    return 0;
}



