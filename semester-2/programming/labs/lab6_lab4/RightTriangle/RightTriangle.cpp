//
// Created by marling on 4/25/23.
//

#include "RightTriangle.hpp"

RightTriangle::RightTriangle(int _height, const std::string& _color, char _symbol, int _x, int _y) :
        Shape (_height, _color, _symbol, _x, _y) {
// std::cout << "Konstruktor triangle\n";
    width = _height;
    Alloc();
    Fill();
}

void RightTriangle::Fill() {
    int i,j;
    for (i = 0; i < height; i++) {
        for (j = 0; j <= i; j++) {
            tab[i][j] = symbol;
        }
    }
}