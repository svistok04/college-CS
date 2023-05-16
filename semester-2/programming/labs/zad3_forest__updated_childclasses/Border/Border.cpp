//
// Created by marling on 4/25/23.
//

#include "Border.hpp"


Border::Border(int _height, int _width, const std::string& _color, char _symbol, int _x, int _y) :
        Rectangle (_height, _color, _symbol, _x, _y) {
    // std::cout << "Konstruktor rectangle\n";
    width = _width;
    Alloc();
    Fill();
}

Border::Border(int _height, const std::string& _color, char _symbol, int _x, int _y) :
        Rectangle (_height, _color, _symbol, _x, _y) {
    // std::cout << "Konstruktor rectangle\n";
    width = _height;
    Alloc();
    Fill();
}

void Border::Fill() {
    int i,j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++)
            tab[i][j] = symbol;
    }

    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            tab[i][j] = '0';
        }
    }
}