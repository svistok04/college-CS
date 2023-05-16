//
// Created by marling on 5/16/23.
//

#ifndef ZAD4_WHEELGAME_WHEEL_HPP
#define ZAD4_WHEELGAME_WHEEL_HPP

class Wheel {
    const int kolo[16] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };
// -1 bankrut
// 0 strata kolejki
public:
    int getValue(int);
};

#endif //ZAD4_WHEELGAME_WHEEL_HPP
