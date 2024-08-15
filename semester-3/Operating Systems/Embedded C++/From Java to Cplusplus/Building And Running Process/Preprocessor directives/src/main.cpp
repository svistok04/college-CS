#include <iostream>
#include "definitions.h"

#if defined(TABLE_SIZE)
int table[TABLE_SIZE];
#endif

int main() {
#if defined(TABLE_SIZE)
    std::cout << "Initialization of the table" << std::endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = i;
    }
#endif
    return 0;
}