

#include <iostream>

int** matrixInitialization(int, int);
void fillWithNumbers(int**, int, int);
void freeA2DMatrix(int**, int);
void printA2DMatrix(int**, int, int);

int main()
{
    srand(time(NULL));

    int rows1, cols1, rows2, cols2, i, j, k;

    printf("Wprowadz rozmiary pierwszej macierzy\n");
    scanf("%d \n %d", &rows1, &cols1);

    printf("Wprowadz rozmiary drugiej macierzy\n");
    scanf("%d \n %d", &rows2, &cols2);

    if (cols2 != rows1)
    {
        printf("These matrices cannot be multiplied, restart the program and try again");
        return 0;
    }

    int** matrix1 = matrixInitialization(rows1, cols1);
    fillWithNumbers(matrix1, rows1, cols1);

    int** matrix2 = matrixInitialization(rows2, cols2);
    fillWithNumbers(matrix2, rows2, cols2);

    int** result = matrixInitialization(rows1, cols2);

    printA2DMatrix(matrix1, rows1, cols1);

    printf("\n");

    printA2DMatrix(matrix2, rows2, cols2);

    printf("\n");

    for (i = 0; i < rows1; ++i)
    {
        for (j = 0; j < cols2; ++j)
        {
            for (k = 0; k < cols1; ++k)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    printA2DMatrix(result, rows1, cols2);

    freeA2DMatrix(matrix1, rows1); freeA2DMatrix(matrix2, rows2); freeA2DMatrix(result, rows1);
}

void fillWithNumbers(int** matrix, int rows, int cols)
{
    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

int** matrixInitialization(int rows, int cols)
{
    int** matrix = (int**)malloc(rows * sizeof(int));
    for (int i = 0; i < cols; i++)
    {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void printA2DMatrix(int** matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeA2DMatrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}