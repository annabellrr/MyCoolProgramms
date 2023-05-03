#include <stdio.h>
#include <math.h>
#include <locale.h>
int* pMassive;
void max(int* pMassive, int n)
{
    int i, max;
    max = *pMassive;
    for (i = 0; i < n; i++)
        if (max < *(pMassive + i)) max = *(pMassive + i);
    printf("������������ �������� � ������� %d\n", max);
}
void min(int* pMassive, int n)
{
    int i, min;
    min = *pMassive;
    for (i = 0; i < n; i++)
        if (min > *(pMassive + i)) min = *(pMassive + i);
    printf("����������� �������� � ������� %d\n", min);
}
void mean(int* pMassive, int n)
{
    int i;
    double mid = 0;
    for (i = 0; i < n; i++)
        mid = mid + *(pMassive + i);
    printf("����� %f\n", mid / n);
}
void RMS(int* pMassive, int n)
{
    int i;
    double midsq = 0, mid = 0;
    for (i = 0; i < n; i++)
        mid = mid + *(pMassive + i);
    mid = mid / n;
    for (i = 0; i < n; i++)
        midsq = midsq + (*(pMassive + i) - mid) * (*(pMassive + i) - mid);
    printf("��� %f", sqrt(midsq / n));
}

int main()
{
    int n, i;
    int* pMassive;
    setlocale(LC_ALL, "Rus");
    printf("����� ���� ����� ��� ������� ����, ���, �������� � ���� �� ���������� ��� ��� ������� ������\n������� ������ ������� ");
    scanf_s("%d", &n);
    pMassive = malloc(sizeof(int) * n); //������ ���� ������ ��� n �����
    printf("������� ������\n");
    for (i = 0; i < n; i++)  scanf_s("%d", pMassive + i);
    max(pMassive, n);
    min(pMassive, n);
    mean(pMassive, n);
    RMS(pMassive, n);
    free(pMassive);
}