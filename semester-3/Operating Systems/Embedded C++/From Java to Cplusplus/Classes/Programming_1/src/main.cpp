#include <iostream>
#include <string>

class Student {
public:
    // constructor
/* Write the constructor without parameters */
/* Write the constructor with parameters  */

    // public methods
/* Write the name() method */
    int age() const { return _age; }
/* Write the isMajor() method */

private:
    // private data fields
    std::string _firstName;
    std::string _lastName;
    int _age;
};

int main() {
    Student s1;
    std::cout << s1.name() << " is major ? " << s1.isMajor() << std::endl;
    Student s2("Abc", "Def", 17);
    std::cout << s2.name() << " is major ? " << s2.isMajor() << std::endl;
    return 0;
}