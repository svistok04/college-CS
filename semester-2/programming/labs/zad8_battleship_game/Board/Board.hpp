//
// Created by marling on 6/6/23.
//

#ifndef ZAD8_BATTLESHIP_GAME_BOARD_HPP
#define ZAD8_BATTLESHIP_GAME_BOARD_HPP


#include <vector>
#include "../Ships/Ship.hpp"

class Board {
    struct Cell {
    private:
        bool hasShip;
        bool hasBeenHit;
        bool isOccupied;

    public:
        Cell() : hasShip(false), hasBeenHit(false), isOccupied(false) {};

        bool getHasShip() const{
            return hasShip;
        }
        bool getHasBeenHit() const{
            return hasBeenHit;
        }
        bool getIsOccupied() const {
            return isOccupied;
        }

        void setHasShip() {
            hasShip = true;
        }
        void setHasBeenHit() {
            hasBeenHit = true;
        }
        void setIsOccupied() {
            isOccupied = true;
        }
    };

    std::vector<std::vector<Cell>> board;

public:
    explicit Board();

    Cell& getCell(const Coordinates&);

    std::string checkIfPossibleToPlace(Coordinates&, int);
    void placeShip(std::vector<Coordinates>&);
    void markCellsAsOccupied(Coordinates&);


    friend class Game;
};


#endif //ZAD8_BATTLESHIP_GAME_BOARD_HPP
