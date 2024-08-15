#include <cstddef>
#include <iostream>

int main() {
    // === Fixed arrays
    // The array size is a constant and is known at compile time
    static constexpr int arraySize = 30;
    int myArray1[arraySize] = {0};      // Constructs an array on the stack
    int* myArray2 = new int[arraySize]; // Constructs an array on the heap

    delete[] myArray2;  // Release manually the heap memory
    myArray2 = nullptr; // Reset variable pointing to released memory

    // === Dynamic arrays
    int varSize = 5;
    int myArray[varSize] = {0};

    // Change an array element
    myArray[0] = 1;
    // Get an array element
    myArray[1] = myArray[0];

    // Sizeof returns the size of a type in bytes, hence we need to divide by
    // the size of the contained objects.
    int size = sizeof(myArray) / sizeof(int);

    std::cout << "Size of the array: " << sizeof(myArray) << std::endl;
    std::cout << "Size of int: " << sizeof(int) << std::endl;
    std::cout << "Array's size: " << sizeof(myArray) / sizeof(int) << std::endl;

    // Standard for loop
    for (int i = 0; i < size; i++) {
        myArray[i] = 1;
    }
    // For each loop
    int total = 0;
    for (int i : myArray) {
        total += i;
    }

    return 0;
}