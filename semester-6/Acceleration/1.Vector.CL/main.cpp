#include <iostream>
#include <random>
#include <ctime>

#define m 1000
#define n 100

void displayMat(int** mat, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
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
    int** A = new int*[m];
    for (int i = 0; i < m; ++i) {
        A[i] = new int[n]{};
        for (int j = 0; j < n; ++j) {
            A[i][j] = dis(gen);
        }
    }

    int** B = new int*[n];
    for (int i = 0; i < n; ++i) {
        B[i] = new int[m]{};
        for (int j = 0; j < m; ++j) {
            B[i][j] = dis(gen);
        }
    }

    int** C = new int*[m];
    for (int i = 0; i < m; ++i)
        C[i] = new int[m]{};

    std::cout << "Matrix A" << std::endl;
    // displayMat(A, m, n);
    std::cout << "Matrix B" << std::endl;
    // displayMat(B, n, m);
    clock_t task1 = clock();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double task1_total = static_cast<double>(clock() - task1) / CLOCKS_PER_SEC;


    std::cout << "Matrix C" << std::endl;
    // displayMat(C, m, m);

    std::cout << "It took " << task1_total << " seconds." << std::endl;

    for (int i = 0; i < m; ++i) {
        delete[] A[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] C;

    for (int i = 0; i < n; ++i)
        delete[] B[i];
    delete[] B;


    // task
    A = new int*[m];
    for (int i = 0; i < m; ++i) {
        A[i] = new int[n]{};
        for (int j = 0; j < n; ++j) {
            A[i][j] = dis(gen);
        }
    }

    for (int i = 0; i < m; ++i) {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}
