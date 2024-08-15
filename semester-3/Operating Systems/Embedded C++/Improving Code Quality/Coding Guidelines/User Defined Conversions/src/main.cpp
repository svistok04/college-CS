#include <cstring>

class String {
public:
    String() {}
    String(const char* szArray) {
        // not implemented
    }
    String(int size) {
        szArray = new char[size];
    }

    operator int() {
        return szArray != nullptr ? strlen(szArray) : 0;
    }

    int getLength() {
        return szArray != nullptr ? strlen(szArray) : 0;
    }

private:
    char* szArray = nullptr;
};

int main() {
    // create a string by calling explicitly the constructor
    String* s1 = new String("s1");
    // create a string by calling implicitly the constructor
    String s2 = "s2";
    // create a string by calling explicitly the constructor
    String* s3 = new String(10);
    // create a string by calling implicitly the constructor
    // this creates a string of size 10 -> is it was it expected ?
    String s4 = 10;
    // '123' will be converted to an int (combining the ASCII values) and this
    // creates a string by calling the constructor with a very big int value
    String s5 = '123';

    // with the int() operator, conversion from String to int become possible
    // Is it really meaningful ?
    // In that case, one should rather define a method for
    // getting the string length.
    int i2 = s2;

    // use of getMe
    i2 = s2.getLength();

    // use of getLength while discarding the return value
    s2.getLength();

    return 0;
}