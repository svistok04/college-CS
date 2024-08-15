#include <cstdint>
#include <iostream>

class RationalNumber
{
public:
    RationalNumber(int32_t n, int32_t d = 1) :
      n(n/gcd(n, d)), d(d/gcd(n,d)) {
    }

    int32_t num() const {
        return n;
    }
    int32_t den() const {
        return d;
    }

    // define the *= operator
    RationalNumber& operator*=(const RationalNumber& rhs)
    {
        int new_n = n * rhs.n / gcd(n * rhs.n, d * rhs.d);
        d = d * rhs.d / gcd(n * rhs.n, d * rhs.d);
        n = new_n;
        return *this;
    }

    // define the == operator
    bool operator==(const RationalNumber& rhs)
    {
        return num() == rhs.num() && den() == rhs.den();
    }

private:
    constexpr int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

    int32_t n;
    int32_t d;
};

// define the << operator for RationalNumber
std::ostream& operator<<(std::ostream& out, const RationalNumber& f)
{
    return out << f.num() << '/' << f.den();
}
// define the operator for accomplishing multiplication of two rational numbers
RationalNumber operator*(RationalNumber lhs, const RationalNumber& rhs)
{
    return lhs *= rhs;
}

int main() {
    RationalNumber f1(3, 8);
    RationalNumber f2(1, 2);
    RationalNumber f3(10, 2);
    std::cout << f1 << " * " << f2 << " = " << f1 * f2 << std::endl
              << f2 << " * " << f3 << " = " << f2 * f3 << std::endl;
    std::cout << (f3 == f2 * 10) << std::endl;
}