#include <stdio.h>
#include <math.h>
#include <locale.h>

 
double Func(float x) { //���������� �������
	double value;
	value = 1 - cosl(x); //�������������� ������ ������������ ���� �������
	return (value);
}

double dFunc(float x) { //����������� � ������������ ���� �������
	double d_value;
	d_value = sinl(x); /*�������������� ������ ������������ ���� �����������
	������� */
	return (d_value);
}

int main()
{
	setlocale(LC_ALL, "Russian");
		printf("��� ��������� ������ ��������� ���� F(x) = 0\
 ������� �������\n������� ��������� ����������� � ��������� ��������\
 ����������\n");
	int i, n = 0;
	double count = 1, numb, S1, S2;
	int s = scanf_s("%lf %d", &numb, &n);
	if (s < 2) {
		printf("�� ����� ������������ ��� ����������");
		return (90);
	}
	for (i = 1; i <= n; i++) { //�� ����������� ��������� ��������
		count /= 10;
	}
	do {
		S1 = numb - (Func(numb) / dFunc(numb));
		S2 = S1 - (Func(S1) / dFunc(S1));
		numb = S2;
	} while ((Func(S1) / dFunc(S1)) > count);
	switch (n) {
	case 0: printf("%.f\n", S2);
		break;
	case 1: printf("%.1f\n", S2);
		break;
	case 2: printf("%.2f\n", S2);
		break;
	case 3: printf("%.3f\n", S2);
		break;
	case 4: printf("%.4f\n", S2);
		break;
	case 5: printf("%.5f\n", S2);
		break;
	default: printf("%lf\n", S2);
		break;
	}
	return 0;
}
