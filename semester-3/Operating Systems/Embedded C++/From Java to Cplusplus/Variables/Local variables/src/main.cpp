#include <iostream>
#include <string>

int main() {
    // Object created on the stack with default constructor
    std::string s1;
    std::cout << "String s1 : " << s1 << std::endl;
    // Object created on the stack with specific constructor
    std::string s2("Hello");
    std::cout << "String s2 : " << s2 << std::endl;
    // Object created on the heap with specific constructor
    std::string* s3 = new std::string("World");
    std::cout << "String s3 : " << s3[0] << std::endl;

    // Copy an object on the stack means that the assignment operator of the
    // class will be applied (usually it involves a deep copy of the object)
    std::string s4 = s2;
    std::cout << "String s4 : " << s4 << std::endl;
    s4[0] = '#';
    std::cout << "String s4 : " << s4 << std::endl;
    std::cout << "String s2 : " << s2 << std::endl;

    // Copying a pointer to an object simply copies the address (reference)
    // In C++, there is no built-in reference counting mechanism and copying
    // a pointer only means copying an address
    std::string* s5 = s3;
    s5->at(0) = '@';
    std::cout << "String s3 : " << s3[0] << std::endl;
    std::cout << "String s5 : " << s5[0] << std::endl;

    // Delete all variables on the heap
    delete s3; s3 = nullptr;
    delete s5; s5 = nullptr;

    return 0;
}