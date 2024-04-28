#include <iostream>

class MaxHeap {
private:
    int* heap;
    int size;
public:
    void siftUp(int index) {
        if (index == 0) {
            return;
        }
        int parentIndex = (index - 1) / 2;
        if(heap[index] > heap[parentIndex]) {
            std::swap(heap[index], heap[parentIndex]);
            siftUp(parentIndex);
        }
    }
    void siftDown(int index, int size) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 1;

        if (leftChild < size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }
        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            siftDown(size, largest);
        }
    }
    MaxHeap(int* arr, int arrSize) :
    heap(arr),
    size(arrSize)
    {
        for (int i = 0; i < size; ++i) {
            siftUp(i);
        }
        for (int i = size - 1; i > 0; --i) {
            std::swap(heap[0], heap[i]);
            siftDown(0, i);
        }
    }
};

int main() {
    int arr[10] = {4, 1, 9, 4, 3, 2, 5, 10, 31, 24};
    auto* someSort = new MaxHeap(arr, sizeof(arr) / sizeof(arr[0]));
    for (const int e : arr) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

// #include <iostream>
// #include <vector>
//
// int leafSearch(const std::vector<int>& a, int i, int end) {
//     while (2 * i + 2 < end) {
//         int rightChild = 2 * i + 2;
//         int leftChild = 2 * i + 1;
//
//         if (a[rightChild] > a[leftChild]) {
//             i = rightChild;
//         } else {
//             i = leftChild;
//         }
//     }
//     if (2 * i + 1 < end) {
//         i = 2 * i + 1;
//     }
//     return i;
// }
//
// void siftDown(std::vector<int>& a, int i, int end) {
//     int j = leafSearch(a, i, end);
//
//     while (a[i] > a[j]) {
//         j = (j - 1) / 2;
//     }
//
//     while (j > i) {
//         std::swap(a[i], a[j]);
//         j = (j - 1) / 2;
//     }
// }
//
// // Function to sift up an element in the heap
// void siftUp(std::vector<int> &a, int end) {
//     while (end > 0) {
//         int parent = (end - 1) / 2;
//         if (a[parent] < a[end]) {
//             std::swap(a[parent], a[end]);
//             end = parent;
//         } else {
//             return;
//         }
//     }
// }
//
// // Function to heapify the array
// void heapify(std::vector<int> &a, int count) {
//     int end = 1;
//
//     while (end < count) {
//         siftUp(a, end);
//         end++;
//     }
// }
//
// void heapSort(std::vector<int>& arr) {
//     int n = arr.size();
//     for (int i = n - 1; i >= 0; --i) {
//         std::swap(arr[0], arr[i]);
//
//         siftDown(arr, 0, i);
//     }
// }
//
// int main() {
//     // Example usage
//     std::vector<int> arr = {4, 10, 3, 5, 1};
//     int size = arr.size();
//
//     heapSort(arr);
//
//     std::cout << "Heapified array: ";
//     for (int num : arr) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;
//
//     return 0;
// }
