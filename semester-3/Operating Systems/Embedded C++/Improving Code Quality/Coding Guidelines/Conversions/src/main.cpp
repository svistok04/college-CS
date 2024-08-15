#include <iostream>
#include <limits>

class Base {
private:
    int32_t _d1 = 0;
public:
    virtual void m1(int32_t i) { _d1 -= i; }
};

class Derived : public Base {
private:
    int32_t _d2 = 1;
public:
    void m1(int32_t i) override { _d2 += i; }
    void m2(int32_t i) { _d2 -= i; }
};

class Unrelated {
private:
    int16_t _d3 = 1;
public:
    void m() { _d3++; }
};

int main() {

    // Declare one variable of each type.
    Base b;
    Derived d;
    Unrelated u;

    //###################
    // USING c-type cast
    // Primitive types casts
    {
        uint32_t ui32 = std::numeric_limits<uint32_t>::max();
        uint16_t ui16 = std::numeric_limits<uint16_t>::max();
        float f = std::numeric_limits<float>::max();
        // Accepted implicit conversions -> those conversions should be explicit since they are narrowing.
        // Note that making them explicit does not change the result but it shows that the conversion is intended.
        // 2^32 - 1 is converted to 4.29... e+09 (precision may be lost)
        f = ui32;
        // 4.29... e+09 is converted to 0
        ui32 = f;
        ui32 = std::numeric_limits<uint32_t>::max();
        // std::numeric_limits<uint32_t>::max() is converted to std::numeric_limits<uint16_t>::max()
        ui16 = ui32;
        // seeing f as a pointer to uint32_t
        uint32_t *pui32 = (uint32_t*) &f;
        uint32_t fAsUint32 = *pui32;

        // Using cast for Base, Derived and Unrelated
        // You can cast almost anything

        // This cast is accepted and correct since Base is a base class to Derived
        // and Naming is a Derived instance
        Base *pb = (Base *) &d;
        // it calls m1 from Derived as expected.
        pb->m1(1);

        // This cast is accepted because a Base instance could be a Derived instance.
        // It is correct because pb is effectively pointing to a Derived instance.
        Derived *pd = (Derived *) pb;
        // it calls m1 from Derived as expected.
        pb->m1(1);

        // But if pb is now pointing to a Base instance it is accepted.
        // One can then call methods of Derived on a Base instance ! -> undefined behavior.
        pb = &b;
        pd = (Derived *) pb;
        // it calls m1 from Base and not Derived...
        pd->m1(1);

        // It is even possible to cast to a type which is totally unrelated to the expression !
        Unrelated *pu = (Unrelated *) &b;
        // it calls m() from Unrelated...
        pu->m();

        // The address of any object can be stored in almost any type (as long as it can store the address)
        uint64_t dummy = (uint64_t) &b;

        // In C++, some c-style casts that would be accepted in C are not accepted
        // Here char cannot store the address to b.
        // The code below does not compile.
        // char ch = (char) &b;
    }

    std::cout << "c-style cast done" << std::endl;

    //###################
    // USING static_cast
    // Primitive types
    // Conversion with static casts behaves similarly to c-type cast.
    // It does however reject casting between unrelated types !
    {
        uint32_t ui32 = std::numeric_limits<uint32_t>::max();
        uint16_t ui16 = std::numeric_limits<uint16_t>::max();
        float f = std::numeric_limits<float>::max();
        f = static_cast<float>(ui32);
        ui32 = static_cast<uint32_t>(f);
        ui32 = std::numeric_limits<uint32_t>::max();
        ui16 = static_cast<uint16_t>(ui32);

        // The code below does not compile
        // uint32_t* pui32 = static_cast<uint32_t*>(&f);


        // Using cast for Base, Derived and Unrelated
        // static_cast prevents conversions between unrelated types.
        Base *pb = static_cast<Base *>(&d);
        Derived *pd = static_cast<Derived *>(pb);
        pb = &b;
        pd = static_cast<Derived *>(pb);
        // this may crash at run time...
        // The code below does not compile
        // Unrelated* pu = static_cast<Unrelated*>(&b);

        // The code below does not compile
        // uint64_t dummy = static_cast<uint64_t>(&b);
    }

    std::cout << "static_cast done" << std::endl;

    //###################
    // USING dynamic_cast
    // Using dynamic_cast requires RTTI. In most cases, for embedded systems, RTTI is disabled.
    // For embedded systems, even more than for other systems, compile-time errors are preferred to run-time errors.
    //
    // dynamic_cast<Type *>(pt) converts the pointer pt to a pointer of type Type *
    // if the pointed-to object (*pt) is of type Type or else derived directly or indirectly from type Type.
    // Otherwise, the expression evaluates to the null pointer.

    // dynamic_cast works only for classes that have virtual functions.
    // dynamic_cast works only when the target type is a pointer or reference to a class type.
    {
        Base *pb = dynamic_cast<Base *>(&d);
        // pb is of type Base which is not derived from Derived.
        // But it will succeed in runtime since the pointed-to object is of type Derived.
        Derived *pd = dynamic_cast<Derived *>(pb);
        pd->m1(1);

        // b is of type Base which is not derived from Unrelated.
        // It cannot succeed in runtime since Base and Unrelated are not related.
        Unrelated* pu = dynamic_cast<Unrelated*>(&b);
        if (pu != nullptr) {
            pu->m();
        }
    }

    std::cout << "Main done" << std::endl;
    return 0;
}
