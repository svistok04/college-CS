#include <iostream>
#include <vector>

// Form class
class Form {
public:
    Form(int edgesNumber,
         int length) : _edgesNumber(edgesNumber), _length(length) { }

     int edgesNumber() const { return _edgesNumber; }
     int length() const { return _length; }

     virtual void print() { std::cout << "Form of " << edgesNumber() <<
        " edges with length " << length() << std::endl; }

private:
    int _edgesNumber;
    int _length;
};

// =============================================================================
// Square class
class Square : public Form {
public:
    Square(int length) : /* Add call to constructor of mother class */ { }
    /* Override the print() method for the expected result */
private:
    static constexpr int kNbrOfEdges = 4;
};

// =============================================================================
// Triangle class
class Triangle : public Form {
public:
    Triangle(int length) : /* Add call to constructor of mother class */ { }

    /* Add the declaration of the overriden print() method */
        int height = length() / 2 + 1;
        int width = 1;
        for (int i = 0; i < height; i++) {
            int space = (length() - width) / 2;
            for (int j = 0; j < space; j++) {
                std::cout << " ";
            }
            for (int k = 0; k < width; k++) {
                std::cout << "*";
            }
            std::cout << std::endl;
            width += 2;
        }
    }
private:
    static constexpr int kNbrOfEdges = 3;
};

// =============================================================================
int main() {
    Form f(5, 7);
    f.print();

    Square s(4);
    s.print();

    Triangle t(5);
    t.print();

    // Expected output:
    // Form of 5 edges with size 7
    // ****
    // ****
    // ****
    // ****
    //   *
    //  ***
    // *****
    return 0;
}