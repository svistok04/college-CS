//
// Created by marling on 3/29/23.
//
#include "../Tree/Tree.hpp"
#include "Forest.hpp"
#include <iostream>
using namespace std;

void Forest::addTree(Tree* t) {
    wektor.push_back(t);
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
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            bool treePrinted = false;
            for (auto t : wektor) {
                if (i >= t->x && i < t->x + t->height && j >= t->y &&
                    j <= t->y + 2 * t->height &&
                    t->tab[i - t->x][j - t->y] == 1) {
                    if (t->color == "green")
                        cout << "\u001b[32m";
                    if (t->color == "red")
                        cout << "\u001b[31m";
                    cout << t->symbol;
                    treePrinted = true;
                    break;
                }
            }
            if (!treePrinted) {
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

    for (auto t : wektor) {
        delete t;
    }
    wektor.clear();

    cout << "The forest has been removed";
}