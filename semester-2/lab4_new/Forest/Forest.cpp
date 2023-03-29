//
// Created by marling on 3/29/23.
//

#include "../Tree/Tree.hpp"
#include "Forest.hpp"
#include <iostream>
using namespace std;

void Forest::addArea() {
    forest = new char *[height];
    for (int i = 0; i < height; i++) {
        forest[i] = new char[width];
        for (int j = 0; j < width; ++j) {
            forest[i][j] = '0';
        }
    }
}

Forest::~Forest() {
    for (auto t : wektor) {
        delete t;
    }
    wektor.clear();

    for (int i = 0; i < height; i++)
        delete[] forest[i];

    delete[] forest;
}

void Forest::addTree(Tree *t) { wektor.push_back(t); }

void Forest::printForest() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            bool treePrinted = false;
            for (auto tree : wektor) {
                if (i >= tree->x && i < tree->x + tree->height && j >= tree->y &&
                    j < tree->y + 2 * tree->height - 1 &&
                    tree->tab[i - tree->x][j - tree->y] == 1) {
                    if (tree->color == "green")
                        cout << "\u001b[32m";
                    if (tree->color == "red")
                        cout << "\u001b[31m";
                    if (tree->color == "magenta")
                        cout << "\u001b[35m";
                    if (tree->color == "blue")
                        cout << "\u001b[34m";
                    if (tree->color == "yellow")
                        cout << "\u001b[33m";
                    cout << tree->symbol;
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

Forest::Forest(int h, int w) {
    height = h;
    width = w;
}