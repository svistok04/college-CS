//
// Created by marling on 6/6/23.
//

#include "Ship.hpp"



Ship::Ship(int length, const Coordinates& initialCoordinate)
        : length(length), coordinate(initialCoordinate) {}


int Ship::getLength() const {
    return length;
}


Coordinates Ship::getCoordinate() {
    return coordinate;
}

std::vector<Coordinates>& Ship::getCoordinates() {
    return coordinates;
}

void Ship::setCoordinate(Coordinates coord) {
    coordinate = coord;
}

void Ship::setCoordinates(const Coordinates& head, bool isHorizontal) {

    coordinates.emplace_back(head);

    int row = head.getRow();
    int column = head.getColumn();
    for (int i = 1; i < length; ++i) {
        if (isHorizontal) {
            coordinates.emplace_back(row, column + i);
        } else {
            coordinates.emplace_back(row - i, column);
        }
    }
}



Carrier::Carrier(int, const Coordinates& coord) : Ship(5, coord) {}

Battleship::Battleship(int, const Coordinates& coord) : Ship(4, coord) {}

Cruiser::Cruiser(int, const Coordinates& coord) : Ship(3, coord) {}

Destroyer::Destroyer(int, const Coordinates& coord) : Ship (2, coord) {}

Submarine::Submarine(int, const Coordinates& coord) : Ship(1, coord) {}