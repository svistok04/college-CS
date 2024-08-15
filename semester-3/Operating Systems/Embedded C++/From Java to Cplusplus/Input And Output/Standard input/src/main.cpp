#include <iostream>
#include <string>

int main() {
    std::string userInput = "";
    std::cout << "Say something : ";
    std::getline(std::cin, userInput);
    std::cout << "Echo : " << userInput << std::endl;

    int n = 0;                          // Declare the variable to hold input
    std::cout << "Please enter n: ";     // Prompt user
    std::cin >> n;                      // Read user input and store in n
    std::cout << "N value is : " << n << std::endl;

    if (std::cin.fail()) {
        std::cerr << "Input error!" << std::endl;
    }

    return 0;
}