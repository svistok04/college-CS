//
// Created by marling on 6/6/23.
//

#ifndef ZAD8_BATTLESHIP_GAME_PLAYER_HPP
#define ZAD8_BATTLESHIP_GAME_PLAYER_HPP


#include "../Board/Board.hpp"
#include "../Ships/ShipManager.hpp"

class Player {
    Board board;
    std::vector<std::shared_ptr<Ship>> ships;
public:
    Player();
    Board& getBoard();
    const std::vector<std::shared_ptr<Ship>> &getShips() const;
};

#endif //ZAD8_BATTLESHIP_GAME_PLAYER_HPP
