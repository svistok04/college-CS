//
// Created by marling on 12/16/23.
//

#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

template<typename T>
struct DynamicArray {
    T* arr;
    int size;
    int capacity;

    DynamicArray() : arr(new T[2]()), size(0), capacity(2) {}
    ~DynamicArray() {
        delete[] arr;
    }

    void push(const T& element) {
        if (size == capacity) {
            capacity *= 2;
            T* newArr = new T[capacity]();
            for (int i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = element;
    }

    void pop() {
        --size;
    }
};

#endif //DYNAMICARRAY_HPP
