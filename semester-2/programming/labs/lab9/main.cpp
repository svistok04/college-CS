#include <iostream>
#include <algorithm>

int main() {
    std::vector<int> v{ 1, 5, 8, 9, 6, 7, 3, 4, 2, 0 };

    sort(v.begin(), v.end());

    std::cout << "Sorted \n";
    for (auto x : v)
        std::cout << x << " ";

    std::vector<int> w{ 1, 5, 8, 9, 6, 7, 3, 4, 2, 0 };

    sort(w.begin(), w.end(), std::greater<>());
    std::cout << "\nSorted \n";
    for (auto x : w)
        std::cout << x << " ";

    return 0;
}


