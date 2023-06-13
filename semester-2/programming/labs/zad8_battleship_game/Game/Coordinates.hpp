//
// Created by marling on 6/7/23.
//

#ifndef ZAD8_BATTLESHIP_GAME_COORDINATES_HPP
#define ZAD8_BATTLESHIP_GAME_COORDINATES_HPP


#include <iostream>
#include <sstream>

class Coordinates {
    int row;
    int column;
public:
    friend std::istream& operator>>(std::istream&, Coordinates&);
    friend std::ostream& operator<<(std::ostream&, const Coordinates&);

    Coordinates(int, int);

    int getRow() const;

    int getColumn() const;

    void setRow(int);

    void setColumn(int);
};

#endif //ZAD8_BATTLESHIP_GAME_COORDINATES_HPP
