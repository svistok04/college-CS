#include <cstdio>
#include <cstdint>

template <typename T, uint32_t queue_sz> class Queue {
public:
    // add other methods
    uint32_t getSize() const {
        return queue_sz;
    }
private:
    T array[queue_sz];
};

template <class T> class Arithmetic {
public:
    Arithmetic(T a, T b) : _a(a), _b(b)
    {

    }

    T add()
    {
        return _a + _b;
    }

    T sub()
    {
        return _a - _b;
    }

private:
    T _a;
    T _b;
};

int main() {
    // use Arithmetic with int
    Arithmetic<int> a1(1, 2);
    printf("Add is %d, sub is %d\n", a1.add(), a1.sub());

    // use Arithmetic with float
    Arithmetic<float> a2(1.5, 2.1);
    printf("Add is %f, sub is %f\n", a2.add(), a2.sub());

    // create a queue of char of size 5
    static constexpr uint32_t kCharQueueSize = 5;
    Queue<char, kCharQueueSize> charQueue;
    printf("char queue size is %d\n", charQueue.getSize());

    // create a queue of int of size 10
    static constexpr uint32_t kIntQueueSize = 10;
    Queue<int, kIntQueueSize> intQueue;
    printf("char queue size is %d\n", intQueue.getSize());

    return 0;
}