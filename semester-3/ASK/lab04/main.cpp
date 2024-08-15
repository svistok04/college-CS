#include <iostream>

int main() {
    uint8_t a = 0x67; // 01100111
    uint8_t c;
//    a &= 0xDA; // 01100111 & 11011010 = 01000010 (0x42)
//    asm("movb %0, %%al" : : "r"(a));
//    asm("movb %%al, %0" : "=a"(c) :);

    asm("movb %0, %1" : "=r"(c) : "r"(a));

    printf("%02X", c);

    return 0;
}
