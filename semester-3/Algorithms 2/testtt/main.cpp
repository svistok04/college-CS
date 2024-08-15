#include <iostream>

int main() {
    std::string lana = "лана дель рей";
    std::string output{};
    for (char ch : lana) {
        output += ch >> 1;
    }
    std::cout << lana << std::endl << output;
}