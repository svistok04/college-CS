#include <iostream>
#include <string>

std::string toLowerCase(std::string s) {
    for (std::string::iterator it = s.begin(); it != s.end(); it++) {
        // '*it' permits to access the character at the address pointed by the
        // iterator
        // use std::tolower for converting the given character to lower case
        // based on the current locale
        *it = std::tolower(*it);
    }
    return s;
}

std::string eraseSpaces(std::string s) {
/* Erase all spaces */
    return s;
}

bool palindrome(std::string s) {
/* Check if the string is a palindrom */
    return true;
}

int main() {
    std::string sPal = "madam";
    sPal = eraseSpaces(sPal);
    sPal = toLowerCase(sPal);
    std::cout << palindrome(sPal) << std::endl;

    sPal = "Do geese see God";
    sPal = eraseSpaces(sPal);
    sPal = toLowerCase(sPal);
    std::cout << palindrome(sPal) << std::endl;

    sPal = "This is not a palindrome";
    sPal = eraseSpaces(sPal);
    sPal = toLowerCase(sPal);
    std::cout << palindrome(sPal) << std::endl;

    return 0;
}