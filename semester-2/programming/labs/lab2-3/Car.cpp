//
// Created by marling on 3/25/23.
//

#include "Car.hpp"
#include <iostream>
using namespace std;

void Car::getFuelType() {
    if (fuelType == 'g') cout << "Gasoline" << endl;
    if (fuelType == 'd') cout << "Diesel" << endl;
}

void Car::getName() {
    cout << name << endl;
}

void Car::getColor() {
    cout << color << endl;
}

Car::Car(string _name, string _color, char _fuelType) {
    name = _name;
    color = _color;
    fuelType = _fuelType;
}