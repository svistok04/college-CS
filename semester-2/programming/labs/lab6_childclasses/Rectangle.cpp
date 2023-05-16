//
// Created by marling on 4/25/23.
//

#include "Rectangle.hpp"

int Shape::counter = 0;

Rectangle::Rectangle(int _height, int _width, std::string _color, char _symbol) :
                    Shape(_height, _color, _symbol) {
    std::cout << "Konstruktor rectangle\n";
    width = _width;
    Alloc();
    Fill();
}

Rectangle::Rectangle(int _height, std::string _color, char _symbol) :
                    Shape (_height, _color, _symbol) {
    std::cout << "Konstruktor rectangle\n";
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

