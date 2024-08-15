#include <iostream>
#include <vector>

int main() {
    // Create a vector containing integers
    std::vector<int> v = {7, 5, 16, 8};

    // Add two more integers at the end of the vector
    v.push_back(25);
    v.push_back(13);
    // Removes the last element
    v.pop_back();

    // Access first element
    std::cout << "First element is : " << v.front() << std::endl;
    // Access last element
    std::cout << "Last element is : " << v.back() << std::endl;

    // Size of the vector
    int size = v.size();

    // Print out the vector
    std::cout << "v = { ";
    for (int i = 0; i < size; i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << "}; \n";

    return 0;
}