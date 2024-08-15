//
// Created by marling on 5/31/23.
//

#ifndef ZAD7_MANDELBROT_SET_FRACTAL_HPP
#define ZAD7_MANDELBROT_SET_FRACTAL_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

class Fractal {
private:
    int iXmax;
    int iYmax;
    double CxMin;
    double CxMax;
    double CyMin;
    double CyMax;
    double PixelWidth;
    double PixelHeight;
    int MaxColorComponentValue = 256;
    std::vector<std::vector<std::vector<unsigned char>>> colorArray;

public:
    Fractal(int iXmax, int iYmax, double cxMin, double cxMax, double cyMin, double cyMax);

    void generateFractal();
    void saveToFile(const std::string&, const std::string&);
};


#endif //ZAD7_MANDELBROT_SET_FRACTAL_HPP
