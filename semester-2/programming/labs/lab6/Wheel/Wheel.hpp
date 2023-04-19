//
// Created by marling on 4/11/23.
//

#ifndef LAB6_WHEEL_H
#define LAB6_WHEEL_H


class Wheel {
    const int kolo[16] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };
// -1 bankrut
// 0 strata kolejki
public:
    int getValue(int);
};


#endif //LAB6_WHEEL_H
