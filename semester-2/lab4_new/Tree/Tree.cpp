//
// Created by marling on 3/29/23.
//

#include "Tree.hpp"
#include "../Forest/Forest.hpp"
#include <iostream>
using namespace std;

Tree::Tree(int _height, string _color, char _symbol, int _x, int _y) {

    int i, j;

    height = _height;
    color = _color;
    symbol = _symbol;
    x = _x;
    y = _y;

    tab = new char* [height];

    for (j = 0; j < height; j++) {
        tab[j] = new char[2 * height - 1];
        for (i = 0; i < 2 * height - 1; i++) {
            tab[j][i] = ' ';
        }
    }

    for (j = 0; j < height; j++) {
        for (i = height - j - 1; i < height + j; i++) {
            tab[j][i] = 1;
        }
    }
}

Tree::~Tree() {
    int j;
    cout << "The tree has been removed" << endl;
    for (j = 0; j < height; j++) {
        delete tab[j];
    }
    delete tab;
}

/*
void Tree::printTree()
{
    int i, j;

    for (j = 0; j < height; j++) {
        for (i = 0; i < 2*height-1; i++) {
            cout << tab[j][i];
        }
        cout << endl;
    }

    if (color == "green") cout << "\003[0m";
    if (color == "red") cout << "\003[0m";

}
*/