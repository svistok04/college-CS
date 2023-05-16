//
// Created by marling on 4/25/23.
//

#include <iostream>
#include "Triangle.hpp"

Triangle::Triangle(int _height, const std::string& _color, char _symbol, int _x, int _y) :
        Shape (_height, _color, _symbol, _x, _y) {
    // std::cout << "Konstruktor triangle\n";
    width = _height;
    Alloc();
    Fill();
}

void Triangle::Print() {
    int i, j;

    std::cout << color;

    for (i = 0; i < height; i++) {
        for (j = 0; j < 2 * width - 1; j++) {
            std::cout << (tab[i][j] != '0' ? tab[i][j] : ' ');
        }
        std::cout << std::endl;
    }
    std::cout << "\033[0m";
}

void Triangle::Fill() {
    int i,j;
    for (i = 0; i < height; i++) {
        for (j = height - i - 1; j < height + i; j++) {
            tab[i][j] = symbol;
        }
    }
}