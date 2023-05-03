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
    
    // Matrix3x3 mat2;
    // mat2.data[0][0] = 7;
    // mat2.data[0][1] = 5;
    // mat2.data[1][1] = 6;
    // mat2.data[2][2] = 2;
    
    print_matrix(&mat1);
    
    printf("\n");
    
    // print_matrix(&mat2);
    
    // printf("\n");
    
    Matrix3x3 invMatrix = inverseMatrix(&mat1);
    
    printf("inverse matrix :\n");
    
    print_matrix(&invMatrix);
    
    printf("\n");
    
    Matrix3x3 mul = multiplyMatrices(&mat1, &invMatrix);
    
    printf("multiplied matrices (should be E) :\n");

    print_matrix(&mul);
    

    return 0;
}