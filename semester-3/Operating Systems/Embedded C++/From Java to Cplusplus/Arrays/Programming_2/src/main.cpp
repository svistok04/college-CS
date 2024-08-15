#include <iostream>
#include <vector>

void starsArrays(int base) {
    // Creation of the array
    char* array[base];
    for (int i = 0; i < base; i++) {
/* Fill the array */
        array[i][base - i] = '\0';
    }
    // Display
    for (int i = 0; i < base; i ++) {
        char* index = array[i];
        // Like in C, '*' is used to access the value at the index address
        // Like in C, index++ increments the address to the next address
        while(*index != '\0') {
            std::cout << *index++;
        }
        std::cout << std::endl;
    }
    // Deletion of the resources (for each new, we must have a delete)
    for (int i = 0; i < base; i++) {
/* Delete the dynamically allocated arrays */
    }
}

void starsVector(int base) {
    std::vector<std::vector<char>> array(base);
/* Fill the array */
    // Display
    // Notice how we know the array sizes with the vector library
    int nbr_rows = array.size();
    for (int i = 0; i < nbr_rows; i++) {
        int nbr_cols = array[i].size();
        for (int j = 0; j < nbr_cols; j++) {
            std::cout << array[i][j];
        }
        std::cout << std::endl;
    }
    // No need to delete, the vector library takes care of it
}

int main() {
    constexpr int BASE = 5;
    starsArrays(BASE);
    starsVector(BASE);
    return 0;
}