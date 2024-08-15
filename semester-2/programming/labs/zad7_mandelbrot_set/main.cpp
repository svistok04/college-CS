#include "Fractal.hpp"

int main() {
    int iXmax = 800;
    int iYmax = 800;
    double CxMin = -2.5;
    double CxMax = 1.5;
    double CyMin = -2.0;
    double CyMax = 2.0;

    Fractal fractal(iXmax, iYmax, CxMin, CxMax, CyMin, CyMax);
    fractal.generateFractal();
    fractal.saveToFile("new1.bin", "# Mandelbrot Set");

    return 0;
}
