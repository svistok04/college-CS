//
// Created by marling on 6/6/23.
//

#ifndef ZAD8_BATTLESHIP_GAME_COMPUTER_HPP
#define ZAD8_BATTLESHIP_GAME_COMPUTER_HPP


#include "../Board/Board.hpp"
#include "../Ships/ShipManager.hpp"


class Computer {
    Board board;
    std::vector<std::shared_ptr<Ship>> ships;

public:
    const std::vector<std::shared_ptr<Ship>> &getShips() const;
    Computer();
    Board& getBoard();
};


#endif //ZAD8_BATTLESHIP_GAME_COMPUTER_HPP
