#include <iostream>

int** matrixInitialization(int, int);

int main() {
    FILE *fptr;
    int rows1, cols1, rows2, cols2, num;

    printf("Enter the row size for martix A:");
    scanf("%d", &rows1);
    printf("Enter the column size for martix A:");
    scanf("%d", &cols1);
    int** matrix1 = matrixInitialization(rows1, cols1);

    printf("Enter the row size for martix B:");
    scanf("%d", &rows2);
    printf("Enter the column size for martix B:");
    scanf("%d", &rows2);
    int** matrix2 = matrixInitialization(rows2, cols2);

    //Accessing file a.txt and storing value in matrixA
    fptr = fopen("cmake-build-debug/matrixA.txt", "r");
    for(int i=0; i<rows1; i++){
        for(int j=0; j<cols1; j++){
            fscanf(fptr, "%d", &num);
            matrix1[i][j] = num;
        }
    }
    fclose(fptr);


    fptr = fopen("cmake-build-debug/matrixB.txt", "r");
    for(int i=0; i<rows2; i++){
        for(int j=0; j<cols2; j++){
            fscanf(fptr, "%d", &num);
            matrix2[i][j] = num;
        }
    }
    fclose(fptr);

    if (rows1 != cols2)
    {
        printf("These matrices cannot be multiplicated, restart the program and try again");
        return 0;
    }

    fptr = fopen("cmake-build-debug/matrixC.txt", "w");
    for (int i = 0; i < rows1; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            int element;
            for (int k = 0; k < cols1; ++k)
            {
                 element += matrix1[i][k] * matrix2[k][j];
            }
            element = 0;
            fprintf(fptr, "%d ", element);
        }
    }
    fclose(fptr);
    printf("Please check the file matrixC.txt for result\n");

    return 0;
}

int** matrixInitialization(int rows, int cols)
{
    int** matrix = (int**)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int*)malloc(rows * sizeof(int));
    }
    return matrix;
}
