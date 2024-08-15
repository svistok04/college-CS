#include <memory>

void function()
{
    // solution with raw pointer
    char* pArray = new char[100];
    // do something with pArray

    // say that we have a
    bool condition = false;
    if (condition) {
        // at this point, a memory leak arises since pArray is not released
        return;
    }

    // call delete []
    delete [] pArray;
    pArray = nullptr;

    // solution with unique_ptr
    // memory will be automatically released when array_ptr is removed from the stack
    std::unique_ptr<char> array_ptr = std::unique_ptr<char>(new char[99]);
    // do something with array_ptr

    if (condition) {
        // no memory leak since the destructor of array_ptr is called
        // and memory is thus released
        return;
    }
}

int main()
{
    function();
    return 0;
}