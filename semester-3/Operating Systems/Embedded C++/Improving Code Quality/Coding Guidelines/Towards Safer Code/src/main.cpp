#include <iostream>

enum UnscopedError { Ok, NotPossible,  NotValid,  DontEvenTry };
enum class ScopedError { Ok, NotPossible,  NotValid,  DontEvenTry };

class SafeClass {
public:
    SafeClass() {}
    explicit SafeClass(int size) {
    }

    [[nodiscard("Why are you discarding me?")]] int getter() {
        return 1;
    }

    UnscopedError m1() {
        return NotPossible;
    }

    [[nodiscard("Why are you discarding me?")]] ScopedError m2() {
        return ScopedError::NotPossible;
    }

private:
};


int main() {
    SafeClass s;

    // Valid use of getter.
    int i = s.getter();

    // Use of getter while discarding the return value.
    // The compiler will issue a warning (and warning may be treated as errors).
    /* if you call s.getter() and discard the return value, you get a warning */

    // m1() returns am unscoped enum that can be converted to int
    // Verifying error codes is thus is very lax.
    int ok = s.m1();

    // the code below does not compile -> cannot be implicitly converted to int
    // ok = s.m2();
    ScopedError rc = s.m2();
    // A ScopedError variable cannot be implicitly be converted to int
    if (rc != ScopedError::Ok) {
       std::cout << "Error " << (int) rc << std::endl;
    }


    return 0;
}