//
// Created by marling on 6/6/23.
//

#ifndef ZAD8_BATTLESHIP_GAME_GAME_HPP
#define ZAD8_BATTLESHIP_GAME_GAME_HPP


#include <iosfwd>
#include <random>
#include <cstdlib>
#include <ctime>
#include "../Board/Board.hpp"
#include "../Player/Player.hpp"
#include "../Computer/Computer.hpp"
#include "Coordinates.hpp"

class Game {
    Player player;
    Computer computer;
    bool isGameOver = false;
    bool isUserWinner = false;
public:
    Player getPlayer();
    Computer getComputer();
    friend std::ostream& operator<<(std::ostream&, Game&);
    void askUserToPlaceShip(const std::string&, const std::size_t&);
    void makeComputerPlaceShips(const std::size_t&);
    void userFire();
    void computerFire();
    void checkGameOver(std::vector<Coordinates>&, std::vector<Coordinates>&);
    void play();
};


#endif //ZAD8_BATTLESHIP_GAME_GAME_HPP
