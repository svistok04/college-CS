#include <iostream>

class Printable {
public:
/* Write the print() method */
};

/* Write the Switch interface */

/* Write the Led class definition */ {
public:
    Led(int intensity): _current_intensity(intensity), _intensity(intensity) { }
    void print() override {
        std::cout << "Led has intensity of " << _current_intensity << std::endl;
    }
/* Write the turnOn() method */
/* Write the turnOff method */

private:
    int _current_intensity;
    const int _intensity;
};

int main() {
    Led l(200);
    l.print();
    l.turnOff();
    l.print();
    l.turnOn();
    l.print();

    Printable& p = l;

    Switch& s = l;
    s.turnOff();
    p.print();
    s.turnOn();
    p.print();

    // Expected output :
    // Led has intensity of 200
    // Led has intensity of 0
    // Led has intensity of 200
    // Led has intensity of 0
    // Led has intensity of 200

    return 0;
}