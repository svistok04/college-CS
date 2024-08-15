#include <iostream>
#include <cstdint>

int main() {
    // Signed data types
    short s = 0;
    int i = 1;
    long l = 2;

    int8_t i8 = 3;      // this variable ranges from -2^7 to +2^7 - 1
    int16_t i16 = 4;    // this variable ranges from -2^15 to +2^15 - 1

    std::cout << "Number of bytes for i : " << sizeof(i) << std::endl;
    std::cout << "Number of bytes for i8 : " << sizeof(i8) << std::endl;
    std::cout << "Number of bytes for i16 : " << sizeof(i16) << std::endl;

    // Unsigned data types
    unsigned short us = 0;
    unsigned int ui = 1;
    unsigned long ul = 2;

    uint8_t ui8 = 5;    // this variable ranges from 0 to 255
    uint16_t ui16 = 6;  // this variable ranges from 0 to 2^16 - 1

    // Floating data types
    float f = 1.2;
    double d = 3.4;

    // Boolean data type
    bool b = true;

    // Character data type
    char c = 'a';

    return 0;
}