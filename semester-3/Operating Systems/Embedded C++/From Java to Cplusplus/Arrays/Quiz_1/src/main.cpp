#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};
    // insert 6 at the position v.begin()
    v.insert(v.begin(), 6);
    // insert twice 5 at the position v.begin()
    v.insert(v.begin(), 2, 5);
    // append 4 at the end of the vector
    v.emplace_back(4);
    // remove the element specified at position --v.end()
    v.erase(--(--v.end()));
    return 0;
}