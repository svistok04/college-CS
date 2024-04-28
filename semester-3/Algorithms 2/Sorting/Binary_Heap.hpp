//
// Created by marling on 12/9/23.
//

#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

template<typename T>
class BinaryHeap {
    T* heapArray;
    int size;
    int mode;

    void siftUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heapArray[index] > heapArray[parentIndex]) {
                std::swap(heapArray[index], heapArray[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void siftDown(int i, int size) {
        int leftChild = 2 * i + 1;
        while (leftChild < size) {
            int rightChild = 2 * i + 2;
            if (rightChild < size && heapArray[rightChild] > heapArray[leftChild]) {
                leftChild = rightChild;
            }
            if (heapArray[i] > heapArray[leftChild]) {
                break;
            }
            std::swap(heapArray[i], heapArray[leftChild]);
            i = leftChild;
            leftChild = 2 * i + 1;
        }
    }
public:
    BinaryHeap(T* externalArray, const int arraySize, const int _mode) :
        heapArray(externalArray),
        size(arraySize),
        mode(_mode)
    {
        if (mode == 0) {
            // bottom-up
            for (int i = size / 2 - 1; i >= 0; i--) {
                siftDown(i, size);
            }
        } else if (mode == 1) {
            // top-down
            for (int i = 1; i < size; ++i) {
                siftUp(i);
            }
        }
    }
    void sort() {
        for (int i = size - 1; i > 0; --i) {
            std::swap(heapArray[0], heapArray[i]);
            siftDown(0, i);
        }
    }
};



#endif //BINARY_HEAP_HPP
