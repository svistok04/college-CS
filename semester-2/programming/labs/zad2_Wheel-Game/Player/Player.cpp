//
// Created by marling on 4/5/23.
//

#include "Player.hpp"

int Player::getKasa() {
    return kasa;
}

int Player::getPortfel() {
    return portfel;
}

string Player::getImie() {
    return imie;
}

void Player::setPortfel(int _portfel) {
    portfel = _portfel;
}

void Player::setKasa(int _kasa) {
    kasa = _kasa;
}

Player::Player(std::string _imie) {
    imie = _imie;
}

Player::~Player() {

}