class Dummy {
public:
    Dummy() { }
};

int main() {
    // Delete an object
    Dummy* d = new Dummy();
    delete d;
    d = nullptr;

    // Delete an array
    constexpr int N = 2;
    Dummy* dummies = new Dummy[N];
    for (int i = 0; i < N; i++) {
        dummies[i] = Dummy();
    }
    delete[] dummies;
    dummies = nullptr;

    return 0;
}