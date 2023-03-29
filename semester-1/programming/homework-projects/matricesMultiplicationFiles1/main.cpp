#include <iostream>

int** matrixInitialization(int, int);
void freeA2DMatrix(int**, int);

int main() {
    FILE* fptr1 = fopen("matrixA.txt", "r");
    FILE* fptr2 = fopen("matrixB.txt", "r");
    FILE* fptr3 = fopen("matrixC.txt", "w");
    int rows1, cols1, rows2, cols2, element, i, j, k;
    int arraySize1[2], arraySize2[2];

    for (i = 0; i < 2; i++)
    {
        fscanf(fptr1, "%d", &arraySize1[i]);
        fscanf(fptr2, "%d", &arraySize2[i]);
    }

    rows1 = arraySize1[0]; cols1 = arraySize1[1];
    rows2 = arraySize2[0]; cols2 = arraySize2[1];



    int** matrix1 = matrixInitialization(rows1, cols1);

    int** matrix2 = matrixInitialization(rows2, cols2);


    // macierz A
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            fscanf(fptr1, "%d", &element);
            matrix1[i][j] = element;
        }
    }




    // macierz B
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            fscanf(fptr2, "%d", &element);
            matrix2[i][j] = element;
        }
    }


    if (rows1 != cols2)
    {
        printf("Tych macierzy nie mozna pomnozyc, zrestartuj program i sprobuj ponownie");
        fclose(fptr1);
        fclose(fptr2);
        fclose(fptr3);
        freeA2DMatrix(matrix1, rows1);
        freeA2DMatrix(matrix2, rows2);
        return 0;
    }

    for (int i = 0; i < rows1; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            element = 0;
            for (int k = 0; k < cols1; ++k)
            {
                element += matrix1[i][k] * matrix2[k][j];
            }
            fprintf(fptr3, "%d ", element);
        }
        fprintf(fptr3, "%s", "\n");
    }

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    printf("Sprawdz wynik w pliku matrixC.txt\n");

    freeA2DMatrix(matrix1, rows1);
    freeA2DMatrix(matrix2, rows2);

    return 0;
}

int** matrixInitialization(int rows, int cols)
{
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeA2DMatrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}





























