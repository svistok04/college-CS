#include <vector>

class Dummy {

};

int main() {
    std::vector<Dummy*> v;
    for (int i = 0; i < 5; i++) {
        v.push_back(new Dummy());
    }
    return 0;
}