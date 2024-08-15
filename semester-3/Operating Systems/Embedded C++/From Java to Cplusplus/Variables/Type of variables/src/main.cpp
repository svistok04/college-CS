#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {7, 5, 16, 8};
    // Iterate over elements of the vector
    for (int n : v) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    // The auto keyword is used to interfere the type of n
    for (auto n : v) {
        std::cout << n << " ";
    }
    return 0;
}