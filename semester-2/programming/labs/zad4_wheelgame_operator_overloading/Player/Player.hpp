//
// Created by marling on 5/16/23.
//

#ifndef ZAD4_WHEELGAME_PLAYER_HPP
#define ZAD4_WHEELGAME_PLAYER_HPP

#include <iostream>


using std::string;

class Player {
private:
    string imie;
    int kasa = 0;
    int portfel = 0; //kasa z wygranych rund

public:
     int getPortfel() const;
     int getKasa() const;
    string getImie() const;
    void setKasa(int);
    Player& operator+=(int val);
    friend bool operator<(const Player&, const Player&);
    Player(string);
    ~Player();
};


#endif //ZAD4_WHEELGAME_PLAYER_HPP
