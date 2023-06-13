//
// Created by marling on 6/6/23.
//

#include "Computer.hpp"

Computer::Computer() {
    ships = ShipManager::createShips();
}

Board& Computer::getBoard() {
    return board;
}

const std::vector<std::shared_ptr<Ship>> &Computer::getShips() const {
    return ships;
}

