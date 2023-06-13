//
// Created by marling on 6/7/23.
//

#include "Coordinates.hpp"

Coordinates::Coordinates(int row, int col) {
    Coordinates::row = row;
    Coordinates::column = col;
}

std::istream& operator>>(std::istream& input, Coordinates& coordinate) {
    std::string sInput;
    bool validInput = false;

    while (!validInput) {
        input >> sInput;
        std::stringstream ss(sInput);
        int rowValue;
        char columnValue;
        if (ss >> rowValue >> columnValue && rowValue >= 1 && rowValue <= 10 && columnValue >= 'a' && columnValue <= 'j') {
            coordinate.row = rowValue - 1;
            coordinate.column = columnValue - 'a';
            validInput = true;
        } else {
            std::cout << "Invalid input, try again: ";
        }
    }

    return input;
}


std::ostream &operator<<(std::ostream& os, const Coordinates& coordinate) {
    return os << coordinate.row << ' '<< coordinate.column;
}

int Coordinates::getRow() const {
    return row;
}

int Coordinates::getColumn() const {
    return column;
}

void Coordinates::setRow(int row) {
    Coordinates::row = row;
}

void Coordinates::setColumn(int column) {
    Coordinates::column = column;
}
