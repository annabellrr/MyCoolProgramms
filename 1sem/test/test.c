#include <stdio.h>
#include <math.h>

typedef struct Complex 
{
    double real;
    double im;
} Complex;

Complex construct(double real, double im)
{
    Complex num;
    num.real = real;
    num.im = im;
    return num;
}

double modOfComplex(Complex* number)
{
    return sqrt(number->real * number->real + number->im * number->im);
}

void readFromFile(const char* filename, Complex* numbers)
{

    FILE* file = fopen(filename, "r");
    int i = 0;
    double real, im;
    while (fscanf(file, "%lf+%lfi", &real, &im) != EOF)
    {
        numbers[i] = construct(real, im);
        i++;
    }
}

void printComplex(Complex* number)
{
    printf("%.2f + i * %.2f\n", number->real, number->im);
}

void printComplexArray(Complex* numbers, int n)
{
    for (int i = 0; i < n; i++)
    {
        printComplex(&numbers[i]);
    }
}

void sortByMod(Complex* nums, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (modOfComplex(&nums[i]) < modOfComplex(&nums[j]))
            {
                Complex temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
}

int main()
{
    Complex array[3];
    readFromFile("numbers.dat", array);
    printComplexArray(array, 3);

    printf("\n");

    sortByMod(array, 3);
    printComplexArray(array, 3);

    return 0;
}