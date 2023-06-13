//
// Created by marling on 6/7/23.
//

#include "ShipManager.hpp"

std::vector<std::shared_ptr<Ship>> ShipManager::createShips() {
    std::vector<std::shared_ptr<Ship>> ships;
    Coordinates coord(-1, -1);
    ships.emplace_back(std::make_shared<Carrier>(0, coord));
    ships.emplace_back(std::make_shared<Battleship>(0, coord));
    ships.emplace_back(std::make_shared<Cruiser>(0, coord));
    ships.emplace_back(std::make_shared<Destroyer>(0, coord));
    ships.emplace_back(std::make_shared<Destroyer>(0, coord));
    ships.emplace_back(std::make_shared<Submarine>(0, coord));
    ships.emplace_back(std::make_shared<Submarine>(0, coord));
    ships.emplace_back(std::make_shared<Submarine>(0, coord));
    return ships;
}