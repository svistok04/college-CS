//
// Created by marling on 4/25/23.
//

#include "Shape.hpp"
#include <iostream>
using namespace std;

void Shape::Print() {
    int i, j;

    cout << color;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (tab[i][j]) {
                cout << color;
                cout << tab[i][j];
            }
            else {
                cout << ' ';
            }
        }
        cout << endl;
    }
    cout << "\033[0m";
}

void Shape::Alloc() {
    int i,j;
    tab = new char*[height];
    for (i = 0; i < height; i++) {
        tab[i] = new char[width];
        for (j = 0; j < width; j++) {
            tab[i][j] = '0';
        }
    }
}

Shape::Shape(int _height, string _color, char _symbol)

{
    int i, j;
    height = _height;
    width = 1;
    symbol = _symbol;
    cout << "Konstruktor Shape z parametrami " << height << " " << color << " " << symbol << "\n";
    if (_color == "green") color = "\033[1;32m";
    if (_color == "red") color = "\033[1;31m";
    if (_color == "yellow") color = "\033[1;33m";
    counter++;
}

Shape::~Shape() {
    int j;
    // cout << "The tree has been removed" << endl;
    for (j = 0; j < height; j++) {
        delete tab[j];
    }
    delete tab;
}

/*void Shape::Fill() {
    int i, j;

    tab = new int* [height];
    for (j = 0; j < height; j++) {
        tab[j] = new int[2 * height - 1];
        for (i = 0; i < 2 * height - 1; i++)
            tab[j][i] = ' ';
    }
    for (j = 0; j < height; j++) {
        for (i = height - j - 1; i < height + j; i++) {
            tab[j][i] = 1;
        }
    }
} */