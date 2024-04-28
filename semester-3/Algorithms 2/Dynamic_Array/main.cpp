// ALGO2 IS1 223A LAB02
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <iostream>
#include <random>
#include <sstream>
#include <ctime>

template <typename T>
struct dynamic_array {
    T* arr;
    int size;
    int capacity;

    dynamic_array() : arr(new T[1]), size(0), capacity(1) {}
    ~dynamic_array() {
        delete[] arr;
    }
};

template <typename T>
void insertEnd(dynamic_array<T>*&, const T&);
template <typename T>
std::string findByPosition(dynamic_array<T>*&, int);
template <typename T>
void changeByPosition(dynamic_array<T>*&, int, const T&);
template <typename T>
void clearAll(dynamic_array<T>*&);
template <typename T>
std::string dynamic_array_toString(dynamic_array<T>*&, int);
template <typename T>
void bubbleSort(dynamic_array<T>*&);

int main() {
//    dynamic_array* da = new dynamic_array();
//    insertEnd(da, 5);
//    insertEnd(da, 1);
//    insertEnd(da, 3);
//    insertEnd(da, 2);
//    insertEnd(da, 4);
//    insertEnd(da, 7);
//    insertEnd(da, 9);
//    insertEnd(da, 6);
//    insertEnd(da, 8);
//    insertEnd(da, 0);
//    std::cout << dynamic_array_toString(da, 1) << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1000);//
//    dynamic_array<int>* da = new dynamic_array<int>();
//
//    const int order = 4;
//    const int n = pow(10, order);
//
//    clock_t t1 = clock();
//
//    double max_time_per_element = 0.0;
//
//    for (int i = 0; i < n; i++) {
//        int someint = distribution(gen);
//        clock_t t1_element = clock();
//        insertEnd(da, someint);
//        clock_t t2_element = clock();
//        double time_per_element = t2_element - t1_element;
//        max_time_per_element = (time_per_element > max_time_per_element) ? time_per_element : max_time_per_element;
//     }
//
//    bubbleSort(da);
//
//    clock_t t2 = clock();
//
//    std::cout << dynamic_array_toString(da, n);
//
//    std::cout << "It took at most " << std::fixed << max_time_per_element / CLOCKS_PER_SEC
//    << " seconds to add a single element" << std::endl;
//    std::cout << "The whole process took " << std::fixed << float(t2- t1) / CLOCKS_PER_SEC << " seconds" << std::endl;

    auto* da = new dynamic_array<std::string>();

    insertEnd<std::string>(da, "some");
    insertEnd<std::string>(da, "some");
    insertEnd<std::string>(da, "some");
    insertEnd<std::string>(da, "some");
    insertEnd<std::string>(da, "some");
    insertEnd<std::string>(da, "ok?");
    insertEnd<std::string>(da, "aa");
    insertEnd<std::string>(da, "ol?");
    insertEnd<std::string>(da, "oh?");



    bubbleSort(da);


    std::cout << dynamic_array_toString(da, 9);

    delete da;
    return 0;
}

template <typename T>
void insertEnd(dynamic_array<T>*& da, const T& data) {
    if (da->size == da->capacity) {
        da->capacity *= 2;
        T* newArr = new T[da->capacity];
        for (int i = 0; i < da->size; i++) {
            newArr[i] = da->arr[i];
        }
        delete[] da->arr;
        da->arr = newArr;
    }
    da->arr[(da->size)++] = data;
}

template <typename T>
std::string findByPosition(dynamic_array<T>*& da, int index) {
    if (index > da->size) {
        return "Failed\n";
    }
    return std::to_string(da->arr[index]);
}

template <typename T>
void changeByPosition(dynamic_array<T>*& da, int index, const T& data) {
    if (index > da->size) {
        return;
    }
    da->arr[index] = data;
}

template <typename T>
void clearAll(dynamic_array<T>*& da) {
    delete[] da->arr;
} // ?

template <typename T>
std::string dynamic_array_toString(dynamic_array<T>*& da, int number) {
    std::stringstream output;

    output << "The array's address is: " << &da << std::endl;
    output << "The array's size is: " << da->size << std::endl;
    output << "The array's capacity is: " << da->capacity << std::endl;

    if (number <= da->size) {

        output << "The " << number << " last elements of the array are: " << std::endl;

        for (int i = 0; i < number; i++) {
            int count = da->size - number + i;
            output << da->arr[count] << std::endl;
        }
    } else {
        output << number << " Exceeds the current size of this array, so the " << da->size
               << " last (all) elements of the array are: " << std::endl;
        for (int i = 0; i < da->size; i++) {
            output << da->arr[da->size - i] << std::endl;
        }
    }

    return output.str();
}

template <typename T>
void bubbleSort(dynamic_array<T>*& da) {
    bool swapped;
    for (int i = 0; i < da->size; i++) {
        swapped = false;
        for (int j = 0; j < da->size - i - 1; j++) {
            if (da->arr[j] > da->arr[j+1]) {
                swap(da->arr[j], da->arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
