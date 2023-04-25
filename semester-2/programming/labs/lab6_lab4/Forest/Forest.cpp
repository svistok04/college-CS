//
// Created by marling on 3/29/23.
//
#include "../Tree/Tree.hpp"
#include "Forest.hpp"
#include "../Shape/Shape.hpp"
#include <iostream>
using namespace std;

/*void Forest::addTree(Tree* t) {
    wektor.push_back(t);
}*/

void Forest::addShape(Shape* s) {
    wektor.push_back(s);
}

void Forest::addArea() {
    forest = new char* [height];
    for (int i = 0; i < height; i++) {
        forest[i] = new char [width];
        for (int j = 0; j < width; ++j) {
            forest[i][j] = '0';
        }
    }
}

void Forest::printForest() {
 /*  cout << wektor.size() << endl;
    for(auto s : wektor)
        cout << "Object properties: x = " << s->x << ", y = " << s->y << ", height = " << s->height << ", symbol = " << s->symbol << endl;


    cout << endl;
    */
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            bool printed = false;
            for (auto s : wektor) {
                if (i >= s->x && i < s->x + s->height && j >= s->y &&
                    j <= s->y + 2 * s->height &&
                    s->tab[i - s->x][j - s->y] == s->symbol) {
                        cout << s->color;
                    cout << s->symbol;
                    printed = true;
                    break;
                }
            }
            if (!printed) {
                cout << "\u001b[0m" << forest[i][j];
            }
        }
        cout << '\n';
    }
}

Forest::Forest(int _height, int _width) {
    height = _height;
    width = _width;
}

Forest::~Forest() {
    for (int i = 0; i < height; i++) {
        delete[] forest[i];
    }

    delete[] forest;

    for (auto s : wektor) {
        delete s;
    }

    wektor.clear();

    cout << "The forest has been removed";
}