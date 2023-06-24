#include <stdio.h>

// структура матрица 
typedef struct Matrix3x3{
    double data[3][3];
    double det;
} Matrix3x3;

// печать матрицы
void print_matrix(Matrix3x3* matrix)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("%.1f\t", matrix->data[i][j]);
        }
        printf("\n");
    }
}

// определитель матрицы
double eval_det(Matrix3x3* matrix)
{
    double det = 0;
    for(int i = 0; i < 3; i++)
        det = det + (matrix->data[0][i] * (matrix->data[1][(i+1)%3]*matrix->data[2][(i+2)%3] - matrix->data[1][(i+2)%3]*matrix->data[2][(i+1)%3]));
    matrix->det = det;
    return det;
}

Matrix3x3 multiplyMatrices(Matrix3x3* matrix1, Matrix3x3* matrix2)
{
    Matrix3x3 finalMatrix;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            finalMatrix.data[i][j] = 0;
            for(int k = 0; k < 3; k++)
            
                finalMatrix.data[i][j] += matrix1->data[i][k] * matrix2->data[k][j]; 
        }
    }
    return finalMatrix;
}

Matrix3x3 inverseMatrix(Matrix3x3* matrix)
{
    Matrix3x3 invMatrix;
    
    double det = eval_det(matrix);
    if((det - 0) < 1e-5) // нельзя сравнивать double и 0
    {
        return invMatrix;
    }
    for(int i = 0; i < 3; i++)
    {
        
        for(int j = 0; j < 3; j++)
        {
            invMatrix.data[j][i] = ((matrix->data[(i+1)%3][(j+1)%3] * matrix->data[(i+2)%3][(j+2)%3])
            - (matrix->data[(i+1)%3][(j+2)%3] * matrix->data[(i+2)%3][(j+1)%3])) / det;
        }
    }
    
    return invMatrix;
}


int main()
{
    printf("matrix :\n");
    
    Matrix3x3 mat1;
    mat1.data[0][0] = 1;
    mat1.data[0][1] = 2;
    mat1.data[1][1] = 2;
    mat1.data[2][2] = 5;
   
    print_matrix(&mat1);
    
    printf("\n");
    
    double det = eval_det(&mat1);
    
    printf("determinant : %lf \n", det);
    

    return 0;
}

//чтение из файла
    // FILE* f=fopen(name1, "rt");
    // if (f == 0) {
    //     printf("error");
    //     return;
    // }
    // int k=0;
    //     while(!feof(f))
    //     {
    //         fscanf(f, "%s", s);
    //         a=atoi(s);
    //         b[i]=a;
    //         i++;
    //     }
    //     for(int  i=0; i<3, i++){
    //         for(int j=0, j<3, j++){
    //             mat1.a[i][j] = b[k];
    //             k++;
    //         }
    //     }
    // }