//
// Created by marling on 6/6/23.
//

#include "Player.hpp"

Player::Player() {
    ships = ShipManager::createShips();
}

Board& Player::getBoard() {
    return board;
}

const std::vector<std::shared_ptr<Ship>>& Player::getShips() const {
    return ships;
}
