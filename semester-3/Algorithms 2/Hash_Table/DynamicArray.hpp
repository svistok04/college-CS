//
// Created by marling on 11/25/23.
//

#ifndef HASH_TABLE_DYNAMICARRAY_HPP
#define HASH_TABLE_DYNAMICARRAY_HPP

#include "LinkedList.hpp"

template<typename T>
struct DynamicArray {
    LinkedList<T>** arr;
    int sizeLists;
    int sizePairs;
    int capacity;
    double capacityLimit;

    DynamicArray() : arr(new LinkedList<T>*[1000]()), sizeLists(0), sizePairs(0), capacity(1000), capacityLimit(0.5) {}
    ~DynamicArray() {
        for (int i = 0; i < capacity; ++i) {
            while (arr[i]) {
                auto* tmp = arr[i];
                arr[i] = arr[i]->next;
                delete tmp;
            }
        }
        delete[] arr;
    }
};


#endif //HASH_TABLE_DYNAMICARRAY_HPP
