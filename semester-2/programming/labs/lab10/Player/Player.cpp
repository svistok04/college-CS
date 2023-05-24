//
// Created by marling on 5/17/23.
//

#include "Player.hpp"

#include <iostream>

std::istream& operator>>(std::istream& input, Player& player) {
    std::cout << "Wpisz nazwisko ";
    input >> player.nazwisko;
    std::cout << "Wpisz wiek ";
    input >> player.wiek;
    return input;
}

std::ofstream& operator<<(std::ofstream& output, Player& player) {
    output << player.nazwisko << std::endl << player.wiek << std::endl;
    return output;
}

std::ostream& operator<<(std::ostream& os, Player& player) {
    return os << "Nazwisko = " << player.nazwisko << ", wiek = " << player.wiek;
}

std::ifstream& operator>>(std::ifstream& input, Player& player) {
    input >> player.nazwisko >> player.wiek;
}

/*void Player::operator()(Player&) {
    std::cout << this;
} // functor */

Player::Player(std::string nazwisko, int wiek) : nazwisko(std::move(nazwisko)), wiek(wiek) {}

const std::string Player::getNazwisko() const {
    return nazwisko;
}

