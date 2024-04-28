// ALGO IS1 223A LAB10
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
const std::complex<double> i(0, 1.0);

std::complex<double>* dft(double*, int);
std::complex<double>* fft_rec(double*, int, int);
std::complex<double>* fft(double*, int);
double err(std::complex<double>*, std::complex<double>*, int);

int main() {
    const int MAX_ORDER = 13;
    const bool PRINT = false;
    std::cout << std::showpos << std::fixed << std::setprecision(3);
    for (int o = 1; o <= MAX_ORDER; ++o) {
        const int N = 1 << o;
        clock_t t{};
        double* f = new double[N]();
        for (int n = 0; n < N; ++n) {
            f[n] = n / static_cast<double>(N);
        }
        t = clock();
        std::cout << std::noshowpos << "N = " << N << std::endl << std::showpos;
        std::complex<double>* cDFT = dft(f, N);
        double dftTime = (clock() - t) / static_cast<double>(CLOCKS_PER_SEC) * 1000;
        if (PRINT) {
            std::cout <<  "DFT: " << std::endl;
            for (int i = 0; i < N; ++i) {
                std::cout << cDFT[i] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "DFT time: " << std::noshowpos << dftTime << std::showpos << "ms" << std::endl;

        t = clock();
        std::complex<double>* cFFT = fft(f, N);
        double fftTime = (clock() - t) / static_cast<double>(CLOCKS_PER_SEC) * 1000;
        if (PRINT) {
            std::cout << "FFT: " << std::endl;
            for (int i = 0; i < N; ++i) {
                std::cout << cFFT[i] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "FFT time: " << std::noshowpos << fftTime << std::showpos << "ms" << std::endl;
            std::cout << "Mean error: " << err(cDFT, cFFT, N)<< std::endl << std::endl;
            delete[] f;
            delete[] cDFT;
            delete[] cFFT;

    }
    return 0;
}

std::complex<double>* dft(double* input, int size) {
    std::complex<double>* result = new std::complex<double>[size]();
    for (int k = 0; k < size; ++k) {
        for (int n = 0; n < size; ++n) {
            // double theta = -2* M_PI * n * k / size;
            // result[k] += input[n] * std::exp(i * theta);
            result[k] += std::polar(input[n], -2 * M_PI * n * k / size);
        }
    }
    return result;
}

std::complex<double>* ftt_rec(double* input, int size, int step) {
    std::complex<double>* result = new std::complex<double>[size]();
    if (size == 1) {
        result[0] = std::complex<double>(input[0], 0);
    } else {
        std::complex<double>* even = ftt_rec(input, size / 2, 2 * step);
        std::complex<double>* odd = ftt_rec(input + step, size / 2, 2 * step);
        for (int k = 0; k < size/2; ++k) {
            std::complex p = even[k];
            double theta = -2* M_PI * k / size;
            std::complex<double> q = odd[k] * std::exp(theta * i);
            // std::complex<double> q = std::polar(1.0, -2 * M_PI * k / size) * odd[k];
            result[k] = p + q;
            result[k + size/2] = p - q;
        }
        delete[] even;
        delete[] odd;
    }
    return result;
}

std::complex<double>* fft(double* input, int size) {
    return ftt_rec(input, size, 1);
}

double err(std::complex<double>* cDFT, std::complex<double>* cFFT, int size) {
    double result{};
    for (int i = 0; i < size; ++i) {
        result += abs(cDFT[i] - cFFT[i]);
    }
    return result/size;
}
