//
// Created by marling on 3/25/23.
//

#ifndef LAB2_3_CAR_HPP
#define LAB2_3_CAR_HPP


class Car {
private:
    string name;
    string color;
    char fuelType;
public:
    Car(string, string, char);
    void getName();
    void getColor();
    void getFuelType();
    ~Car() {
        cout << "Destruction" << endl;
    }
};


#endif //LAB2_3_CAR_HPP
