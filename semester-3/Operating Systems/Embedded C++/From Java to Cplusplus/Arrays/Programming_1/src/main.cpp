#include <iostream>
#include <stdexcept>
#include <vector>

int min(const int myArray[], int size) {
    if (size <= 0)
        throw std::invalid_argument("Array is empty.");
/* Search the min value of the array */
}

int max(const int *myArray, int size) {
    if (size <= 0)
        throw std::invalid_argument("Array is empty.");
/* Search the max value of the array */
}

std::vector<int> swap(std::vector<int> v) {
    int size = v.size();
    std::vector<int> v2(0, size);
/* Swap the content of the given array into v2 */
    return v2;
}

int main() {
    // === Using min() with array on the stack
    int myArray1[] = {-1, 2, -3, 4, -5, 6};
    int size1 = /* Compute the size of the array */
    std::cout << min(myArray1, size1) << std::endl;

    // === Using max() with array on the heap
    int* myArray2 = new int[] {-1, 2, -3, 4, -5, 6};
    int size2 = 6; // The size can't be computed
    std::cout << max(myArray2, size2) << std::endl;
    /* Delete the array from the heap */
    myArray2 = nullptr;

    // === Using swap with vector
    std::vector<int> v1 = {1, 2, 3, 4, 5, 6};
    std::vector<int> v2 = swap(v1);
    for (int i: v2) {
        std::cout << i;
    }

    return 0;
}