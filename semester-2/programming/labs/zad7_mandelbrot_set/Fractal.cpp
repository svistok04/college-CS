//
// Created by marling on 5/31/23.
//

#include "Fractal.hpp"

void Fractal::generateFractal() {
    double Cx, Cy;
    double Zx, Zy;
    double Zx2, Zy2;
    int Iteration;
    const int IterationMax = 200;
    const double EscapeRadius = 2;
    double ER2 = EscapeRadius * EscapeRadius;

    for (int iY = 0; iY < iYmax; iY++) {
        Cy = CyMin + iY * PixelHeight;
        if (std::fabs(Cy) < PixelHeight / 2)
            Cy = 0.0;

        for (int iX = 0; iX < iXmax; iX++) {
            Cx = CxMin + iX * PixelWidth;
            Zx = 0.0;
            Zy = 0.0;
            Zx2 = Zx * Zx;
            Zy2 = Zy * Zy;

            for (Iteration = 0; Iteration < IterationMax && ((Zx2 + Zy2) < ER2); Iteration++) {
                Zy = 2 * Zx * Zy + Cy;
                Zx = Zx2 - Zy2 + Cx;
                Zx2 = Zx * Zx;
                Zy2 = Zy * Zy;
            }

            if (Iteration == IterationMax) {
                colorArray[iY][iX][0] = 0;     // Black
                colorArray[iY][iX][1] = 0;
                colorArray[iY][iX][2] = 0;
            } else {
                colorArray[iY][iX][0] = 255;   // White
                colorArray[iY][iX][1] = 255;
                colorArray[iY][iX][2] = 255;
            }
        }
    }
}


void Fractal::saveToFile(const std::string& filename, const std::string& comment) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write the comment to the file
    file.write(comment.data(), comment.size());
    file.write("\n", 1);

    // Write the dimensions and color component value to the file
    file.write(reinterpret_cast<const char*>(&iXmax), sizeof(iXmax));
    file.write(reinterpret_cast<const char*>(&iYmax), sizeof(iYmax));
    file.write(reinterpret_cast<const char*>(&MaxColorComponentValue), sizeof(MaxColorComponentValue));

    // Write the colorArray to the file
    for (const auto& row : colorArray) {
        for (const auto& pixel : row) {
            file.write(reinterpret_cast<const char*>(pixel.data()), sizeof(unsigned char) * 3);
        }
    }

    file.close();
    std::cout << "Binary file '" << filename << "' has been generated." << std::endl;
}


Fractal::Fractal(int iXmax, int iYmax, double cxMin, double cxMax, double cyMin, double cyMax) : iXmax(iXmax),
                                                                                                 iYmax(iYmax),
                                                                                                 CxMin(cxMin),
                                                                                                 CxMax(cxMax),
                                                                                                 CyMin(cyMin),
                                                                                                 CyMax(cyMax) {}

