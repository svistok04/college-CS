//
// Created by marling on 6/7/23.
//

#ifndef ZAD8_BATTLESHIP_GAME_SHIPMANAGER_HPP
#define ZAD8_BATTLESHIP_GAME_SHIPMANAGER_HPP


#include <memory>
#include "Ship.hpp"

class ShipManager {
public:
    static std::vector<std::shared_ptr<Ship>> createShips();
};


#endif //ZAD8_BATTLESHIP_GAME_SHIPMANAGER_HPP
