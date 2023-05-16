//
// Created by marling on 4/25/23.
//

#include "Rectangle.hpp"
#include <iostream>

int Shape::counter = 0;

Rectangle::Rectangle(int _height, int _width, const std::string& _color, char _symbol, int _x, int _y) :
        Shape (_height, _color, _symbol, _x, _y) {
   // std::cout << "Konstruktor rectangle\n";
    width = _width;
    Alloc();
    Fill();
}

Rectangle::Rectangle(int _height, const std::string& _color, char _symbol, int _x, int _y) :
        Shape (_height, _color, _symbol, _x, _y) {
   // std::cout << "Konstruktor rectangle\n";
    width = _height;
    Alloc();
    Fill();
}

void Rectangle::Fill() {
    int i,j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++)
            tab[i][j] = symbol;
    }
}