#include <iostream>
#include <string>

int main() {
    std::string s1 = "Hello";
    std::string s2 = "world";

    // Concatenation
    std::string s = s1 + " " + s2;
    std::cout << s << std::endl;

    // Not possible
    // std::string x = "10";
    // int y = 20;
    // std::string z = x + y;

    // Length
    std::cout << "String length : " << s.length() << std::endl;
    // The size method is an alias for length
    std::cout << "String length : " << s.size() << std::endl;

    // Get the first character
    std::cout << "The first character is : " << s[0] << std::endl;
    // Change the first character
    s[0] = 'h';
    std::cout << s << std::endl;

    // The backslash character turns special characters into string characters
    std::cout << "\"Hello world\"" << std::endl;

    return 0;
}