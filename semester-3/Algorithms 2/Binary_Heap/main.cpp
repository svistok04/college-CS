//ALGO2 IS1 223A LAB05
//Vladyslav Zosimchuk
//zv53855@zut.edu.pl

#include <iostream>
#include <sstream>
#include <random>
#include "DynamicArray.hpp"

template<typename T>
class BinaryHeap {
    DynamicArray<T>* da;
    int mode;

public:
    explicit BinaryHeap(int _mode) :
        da(new DynamicArray<T>()),
        mode(_mode)
    {}
    ~BinaryHeap() {
        delete da;
    };

    void insertNewNode(const T&); // a
    std::string getAndRemoveRoot(); // b
    void clearBH(); // c
    std::string node_to_string(int);
    std::string BH_to_string(); // d
    void heapifyUp(int); // e
    void heapifyDown(int); // f
};

int main() {
//    std::string input;
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dis(0, 100000);
//    const int MAX_ORDER = 7;
//    BinaryHeap<int> myBH(1);
//    for (int o = 1; o <= MAX_ORDER; ++o) {
//        const int n = pow(10, o);
//        clock_t t1 = clock();
//        for (int i = 0; i < n; ++i) {
//            myBH.insertNewNode(dis(gen));
//        }
//        clock_t t2 = clock();
//        std::cout << myBH.BH_to_string();
//        std::cout << "It took " << float(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms to add " << n
//                  << " objects to a binary heap" << std::endl;
//        myBH.clearBH();
//    }
    BinaryHeap<int> myBH(1);
    myBH.insertNewNode(5);
    myBH.insertNewNode(3);
    myBH.insertNewNode(2);
    myBH.insertNewNode(7);
    myBH.insertNewNode(12);
    myBH.insertNewNode(15);
    myBH.insertNewNode(4);
    myBH.insertNewNode(6);
    myBH.insertNewNode(10);
    std::cout << myBH.BH_to_string();
    std::cout << myBH.getAndRemoveRoot();
    std::cout << myBH.BH_to_string();
    myBH.clearBH();
    std::cout << myBH.BH_to_string();
    return 0;
}

template<typename T>
void BinaryHeap<T>::insertNewNode(const T& data) {
//    for (int i = 0; i < da->size; ++i) {
//        if (da->arr[i] == data) return;
//    }
    da->insertEnd(da, data);
    heapifyUp(da->size - 1);
}

template<typename T>
std::string BinaryHeap<T>::getAndRemoveRoot() {
    std::stringstream ss;

    if (da->size == 0) {
        return "Heap is empty.";
    }
    ss << "Removed the root node: " << node_to_string(0);
    da->arr[0] = da->arr[da->size - 1];
    --da->size;
    heapifyDown(0);

    return ss.str();
}

template<typename T>
void BinaryHeap<T>::clearBH() {
    auto newDA = new DynamicArray<T>;
//    for (int i = 0; i < newDA->capacity; ++i) {
//        newDA->arr[i] = 0;
//    }
    delete da;
    da = newDA;
}

template<typename T>
std::string BinaryHeap<T>::node_to_string(int index) {
    std::stringstream ss;
    std::string p = (index != 0) ? std::to_string((index - 1) / 2) : "NULL";
    std::string l = (2 * index + 1 < da->size) ? std::to_string(2 * index + 1) : "NULL";
    std::string r = (2 * index + 2 < da->size) ? std::to_string(2 * index + 2) : "NULL";

    ss << "(" << index << ": [" << " p: " << p << ", l: " << l << ", r: " << r << "], data: " << da->arr[index];
    (index + 1 != da->size) ? ss << "), " : ss << ")";
    ss << std::endl;
    return ss.str();
}

template<typename T>
std::string BinaryHeap<T>::BH_to_string() {
    std::stringstream ss;
    ss << "The number of elements in the binary heap is: " << da->size << std::endl;
    for (int i = 0; i < da->size; ++i) {
        ss << node_to_string(i);
    }
    return ss.str();
}

template<typename T>
void BinaryHeap<T>::heapifyUp(int index) {
    if (mode == 1) {
        if (da->arr[index] > da->arr[(index - 1) / 2]) {
            std::swap(da->arr[index], da->arr[(index - 1) / 2]);
            heapifyUp((index - 1) / 2);
        }
    } else if (mode == 2) {
        if (da->arr[index] < da->arr[(index - 1) / 2]) {
            std::swap(da->arr[index], da->arr[(index - 1) / 2]);
            heapifyUp((index - 1) / 2);
        }
    } else {
        return;
    }
}

template<typename T>
void BinaryHeap<T>::heapifyDown(int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int largestChildIndex = index;

    if (mode == 1) {
        if (da->arr[leftChildIndex] > da->arr[largestChildIndex]) {
            largestChildIndex = leftChildIndex;
        }
        if (da->arr[rightChildIndex] > da->arr[largestChildIndex]) {
            largestChildIndex = rightChildIndex;
        }
    } else if (mode == 2) {
        if (da->arr[leftChildIndex] < da->arr[largestChildIndex]) {
            largestChildIndex = leftChildIndex;
        }
        if (da->arr[rightChildIndex] < da->arr[largestChildIndex]) {
            largestChildIndex = rightChildIndex;
        }
    } else {
        return;
    }

    if (largestChildIndex != index) {
        std::swap(da->arr[index], da->arr[largestChildIndex]);
        heapifyDown(largestChildIndex);
    }
}
