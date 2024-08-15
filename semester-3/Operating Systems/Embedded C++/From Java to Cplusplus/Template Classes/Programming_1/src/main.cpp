#include <iostream>

namespace prog_1 {/* Define the template max() function */
}

int main() {
    std::cout << prog_1::max(5, 6) << std::endl;
    std::cout << prog_1::max(5.1, 5.9) << std::endl;
    std::cout << prog_1::max("abc", "abd") << std::endl;

    return 0;
}