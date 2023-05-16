//
// Created by marling on 5/16/23.
//

#include "Player.hpp"

int Player::getKasa() const {
    return kasa;
}

 int Player::getPortfel() const {
    return portfel;
}

string Player::getImie() const {
    return imie;
}


void Player::setKasa(int _kasa) {
    kasa = _kasa;
}

Player::Player(std::string _imie) {
    imie = _imie;
}

Player::~Player() {

}