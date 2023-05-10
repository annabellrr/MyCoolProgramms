#define CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

typedef struct matrixNxM
{
    float* data;
    int n;
    int m;
}matrixNxM;

//Инициализация матрицы NxM
matrixNxM initMatrix(int n, int m)
{
    matrixNxM matrix;
    matrix.n = n;
    matrix.m = m;
    matrix.data = malloc(sizeof(float) * n * m);
    if (matrix.data == NULL)
    {
        matrix.n = 0;
        matrix.m = 0;
    }
    return matrix;
}

//Заполнение матрицы случайными значениями
void RandomMatrix(matrixNxM matrix)
{
    for (int i = 0; i < matrix.n * matrix.m; i++)
        *(matrix.data + i) = rand();
}

//Matrix file input
matrixNxM Read(FILE* fp)
{
    int n, m;
    matrixNxM matrix;
    fscanf_s(fp, "%d", &n);
    fscanf_s(fp, "%d", &m);
    matrix = initMatrix(n, m);
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.m; j++)
        {
            fscanf_s(fp, "%f", matrix.data + i * matrix.n + j);
        }
    }
    return matrix;
}

//Вывод матрицы
void print(matrixNxM matrix)
{
    int i, j;
    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.m; j++)
            printf("\t %.2f", *(matrix.data + i * matrix.n + j));
        printf("\n");
    }
    printf("\n");
}

void PrintFile(matrixNxM matrix)
{
    int i, j;
    FILE* fp;
    fp = fopen("Result.txt", "w");

    for (i = 0; i < matrix.n; ++i)
    {
        for (j = 0; j < matrix.m; j++)
            fprintf(fp, "%f\t", *(matrix.data + i * matrix.n + j));
        fprintf(fp, "\n");
    }
    fclose(fp);
}

//Сумма матриц Need free
matrixNxM Sum(matrixNxM a, matrixNxM b)
{
    int i, j;
    matrixNxM res;
    res = initMatrix(a.n, a.m);
    if ((a.n != b.n) || (a.m != b.m))
    {
        res.n = 0;
        res.m = 0;

        return res;
    }

    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++)
            *(res.data + i * res.n + j) = *(a.data + i * a.n + j) + *(b.data + i * b.n + j);
    }
    printf("\nSum matrix:\n");
    return res;

}

//Произведение матриц Need free
matrixNxM mult(matrixNxM a, matrixNxM b)
{
    matrixNxM res;
    int i, k, j;
    res = initMatrix(a.n, b.m);
    if (a.m != b.n)
    {
        res.n = 0;
        res.m = 0;
        return res;

    }

    for (i = 0; i < a.n; i++)
    {
        for (j = 0; j < b.m; j++)
        {
            *(res.data + i * res.n + j) = 0;
            for (k = 0; k < a.m; k++)
                *(res.data + i * res.n + j) += *(a.data + i * a.n + k) * *(b.data + k * b.n + j);
        }
    }
    printf("\nMultiplication:\n");
    return res;
}

//Минор Need free()
matrixNxM minor(matrixNxM matrix, int i0, int j0)
{
    int x, y;
    x = 0;
    y = 0;
    matrixNxM minor;
    minor = initMatrix(matrix.n - 1, matrix.m - 1);
    for (int i = 0; i < matrix.n; i++)
    {
        if (i != i0)
        {
            for (int j = 0; j < matrix.m; j++)
            {
                if (j != j0)
                {
                    *(minor.data + x * minor.n + y) = *(matrix.data + i * matrix.n + j);
                    y = y + 1;
                }
            }
            x = x + 1;
            y = 0;
        }
    }
    return minor;
}

//Определитель
float Det(matrixNxM matrix)
{
    float det = 0;
    int sgn = 1;
    matrixNxM mr;
    if (matrix.n != matrix.m)
        return 0;
    if (matrix.n == 1)
        return *(matrix.data);
    for (int i = 0; i < matrix.n; i++)
    {
        mr = minor(matrix, 0, i);
        det += *(matrix.data + 0 * matrix.n + i) * sgn * Det(mr);
        sgn = sgn * (-1);
    }

    return det;
}

//Обратная Need free()
matrixNxM inverse(matrixNxM matrix)
{
    matrixNxM res, mr;
    res = initMatrix(matrix.n, matrix.m);
    if (matrix.n != matrix.m)
    {
        res.m = 0;
        res.n = 0;

        return res;
    }
    float det;
    det = Det(matrix);
    if (det == 0)
    {
        res.n = 0;
        res.m = 0;

        return res;
    }
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.m; j++)
        {
            mr = minor(matrix, j, i);
            if ((i + j) / 2 * 2 == (i + j))
                *(res.data + i * res.n + j) = Det(mr) / det;
            else
                *(res.data + i * res.n + j) = (-1) * Det(mr) / det;
        }
        printf("\nInverse matrix:\n");
        return res;
    }
}
void Check(FILE* fp)
{
    if (fp == NULL)
    {
        printf("Error!");
        return;
    }
}
void main()
{
    int dir, n, m;
    matrixNxM a, b, res;
    printf("where to get the matrix, 1=File, 2=Random\n");
    scanf_s("%d", &dir);
    FILE* asrc = fopen("asrc.txt", "r");
    FILE* bsrc = fopen("bsrc.txt", "r");
    Check(asrc);
    Check(bsrc);

    switch (dir)
    {
    case 1:
        a = Read(asrc);
        b = Read(bsrc);
        break;
    case 2:
        printf("Write n=row and m=column\n");

        scanf_s("%d", &n);
        scanf_s("%d", &m);

        a = initMatrix(n, m);
        printf("Write n=row and m=column\n");
        scanf_s("%d", &n);
        scanf_s("%d", &m);

        b = initMatrix(n, m);
        RandomMatrix(a);
        RandomMatrix(b);
        break;

    default:
        printf("ERROR");
        return;
    }

    printf("\nmatrix A from file:\n");
    print(a);

    printf("\nmatrix B from file:\n");
    print(b);

    res = Sum(a, b);
    print(res);
    PrintFile(res);
    free(res.data);
    res = mult(a, b);
    print(res);
    free(res.data);
    printf("\nDeterminant a: %f\n", Det(a));
    printf("Determinant b: %f\n", Det(b));
    res = inverse(a);
    print(res);
    free(res.data);
    free(a.data);
    free(b.data);
}