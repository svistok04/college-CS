//
// Created by marling on 3/25/23.
//

#include <iostream>
using namespace std;

#include "Fruit.hpp"

void Fruit::getColor() {
    cout << color << endl;
}

void Fruit::getName() {
    cout << name << endl;
}

Fruit::Fruit(string _name, string _color) {
    name = _name;
    color = _color;
}