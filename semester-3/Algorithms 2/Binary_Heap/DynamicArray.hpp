//
// Created by marling on 11/23/23.
//

#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

template <typename T>
struct DynamicArray {
    T* arr;
    int size;
    int capacity;

    DynamicArray() : arr(new T[1]), size(0), capacity(1) {}
    ~DynamicArray() {
        delete[] arr;
    }

    void insertEnd(DynamicArray<T>*& da, const T& data) {
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
};



#endif //DYNAMICARRAY_HPP
