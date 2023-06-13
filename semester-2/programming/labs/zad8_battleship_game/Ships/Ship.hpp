//
// Created by marling on 6/6/23.
//

#ifndef ZAD8_BATTLESHIP_GAME_SHIP_HPP
#define ZAD8_BATTLESHIP_GAME_SHIP_HPP


#include "../Game/Coordinates.hpp"
#include <vector>

class Ship {
    int length;
    Coordinates coordinate;
    std::vector<Coordinates> coordinates;
    std::vector<Coordinates> shellCoordinates;
public:
    explicit Ship(int length, const Coordinates &initialCoordinate);

    int getLength() const;
    void setCoordinate(Coordinates);
    Coordinates getCoordinate();
    void setCoordinates(const Coordinates&, bool);
    std::vector<Coordinates>& getCoordinates();

};

class Carrier : public Ship {
public:
    explicit Carrier(int, const Coordinates&);
};

class Battleship : public Ship {
public:
    explicit Battleship(int, const Coordinates&);
};

class Cruiser : public Ship {
public:
    explicit Cruiser(int, const Coordinates&);
};

class Destroyer : public Ship {
public:
    explicit Destroyer(int, const Coordinates&);
};

class Submarine : public Ship {
public:
    explicit Submarine(int, const Coordinates&);
};


#endif //ZAD8_BATTLESHIP_GAME_SHIP_HPP
