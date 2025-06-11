#include <iostream>
#include <random>
#include <ctime>

#define mMacro 1000
#define nMacro 100


int** allocMat(int rows, int cols) {
    int** mat = new int*[rows];
    for (int i = 0; i < rows; ++i)
        mat[i] = new int[cols]{};
    return mat;
}


void fillMat(int** mat, int rows, int cols, std::mt19937& gen) {
    std::uniform_int_distribution dis(0, 10);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mat[i][j] = dis(gen);
}


void freeMat(int** mat, int rows) {
    for (int i = 0; i < rows; ++i)
        delete[] mat[i];
    delete[] mat;
}

int** mulMat(int** A, int** B, int m, int n, int k) {
    int** C = allocMat(m, k);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < k; ++j)
            for (int x = 0; x < n; ++x)
                C[i][j] += A[i][x] * B[x][j];
    return C;
}


int** transposeMat(int** mat, int rows, int cols) {
    int** T = allocMat(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            T[j][i] = mat[i][j];
        }
    }
    return T;
}

void displayMat(int** mat, int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(0, 10);
    // task 1 matrix mul
    int** A = new int*[mMacro];
    for (int i = 0; i < mMacro; ++i) {
        A[i] = new int[nMacro]{};
        for (int j = 0; j < nMacro; ++j) {
            A[i][j] = dis(gen);
        }
    }

    int** B = new int*[nMacro];
    for (int i = 0; i < nMacro; ++i) {
        B[i] = new int[mMacro]{};
        for (int j = 0; j < mMacro; ++j) {
            B[i][j] = dis(gen);
        }
    }

    int** C = new int*[mMacro];
    for (int i = 0; i < mMacro; ++i)
        C[i] = new int[mMacro]{};

    // std::cout << "Matrix A" << std::endl;
    // displayMat(A, m, n);
    // std::cout << "Matrix B" << std::endl;
    // displayMat(B, n, m);
    clock_t task1 = clock();
    for (int i = 0; i < mMacro; ++i) {
        for (int j = 0; j < mMacro; ++j) {
            for (int k = 0; k < nMacro; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double task1_total = clock() - task1;
    // std::cout << "Matrix C" << std::endl;
    // displayMat(C, m, m);

    std::cout << "it took " << task1_total << " ms to multiply two matrices (1000x100 and 100x1000)" << std::endl;




    // task 2 transpose
    clock_t task2 = clock();
    int** AT = new int*[nMacro];
    for (int i = 0; i < nMacro; ++i) {
        AT[i] = new int[mMacro]{};
        for (int j = 0; j < mMacro; ++j){
            AT[i][j] = A[j][i];
        }
    }
    double task2_total = clock() - task2;
    std::cout << "it took " << task2_total << " ms to transpose a (" << mMacro << "x" << nMacro << ") matrix\n";
    for (int i = 0; i < nMacro; ++i) {
        delete[] AT[i];
    }
    delete[] AT;

    for (int i = 0; i < mMacro; ++i) {
        delete[] A[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] C;

    for (int i = 0; i < nMacro; ++i)
        delete[] B[i];
    delete[] B;


    // task 3 different sizes
    const int numTests = 3;

    int sizes[2 * numTests][2] = {
        {700, 2500}, {2500, 1000},
        {500, 1500}, {1500, 800},
        {1200, 3600}, {3600, 900}
    };

    int** arrays[2 * numTests];


    for (int i = 0; i < 2 * numTests; ++i) {
        int rows = sizes[i][0];
        int cols = sizes[i][1];
        arrays[i] = allocMat(rows, cols);
        fillMat(arrays[i], rows, cols, gen);
    }

    for (int i = 0; i < 2 * numTests; i += 2) {
        int m = sizes[i][0];
        int n = sizes[i][1];
        int k = sizes[i + 1][1];

        clock_t start = clock();
        int** C = mulMat(arrays[i], arrays[i + 1], m, n, k);
        double ms = clock() - start;
        std::cout << "it took " << ms << " ms to multiply matrices ("
                  << m << "x" << n << ") * (" << n << "x" << k << ")\n";

        freeMat(C, m);
    }

    for (int i = 0; i < 2 * numTests; ++i) {
        int rows = sizes[i][0];
        int cols = sizes[i][1];

        clock_t start = clock();
        int** T = transposeMat(arrays[i], rows, cols);
        double ms = clock() - start;

        std::cout << "it took " << ms << " ms to transpose a (" << rows << "x" << cols << ") matrix\n";


        freeMat(T, cols);
    }

    for (int i = 0; i < 2 * numTests; ++i) {
        int rows = sizes[i][0];
        freeMat(arrays[i], rows);
    }
    return 0;
}
