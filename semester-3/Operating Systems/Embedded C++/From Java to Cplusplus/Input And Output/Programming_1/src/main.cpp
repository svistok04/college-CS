#include <iostream>
#include <string>

int sum(int value) {
    int sum = 0;
    for (int i = 1; i <= value; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    int value = 0;
/* Get the user input */
    try {
        value = std::stoi(userInput);
    } catch (std::invalid_argument const& e) {
        /* Put the message in the standard error */ << "std::invalid_argument::what():" << e.what() << std::endl;
        return -1;
    } catch (std::out_of_range const& e) {
        /* Put the message in the standard error */ << "std::out_of_range::what():" << e.what() << std::endl;
        return -1;
    }

    int total = sum(value);
    /* Put the message in the standard output */ << "Sum of " << value << " is " << total << std::endl;
    return 0;
}