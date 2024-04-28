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
};

#endif //DYNAMICARRAY_HPP
