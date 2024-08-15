#include <iostream>
#include <vector>

int leafSearch(const std::vector<int>& a, int i, int end) {
    while (2 * i + 2 < end) {
        int rightChild = 2 * i + 2;
        int leftChild = 2 * i + 1;

        if (a[rightChild] > a[leftChild]) {
            i = rightChild;
        } else {
            i = leftChild;
        }
    }
    if (2 * i + 1 < end) {
        i = 2 * i + 1;
    }
    return i;
}

void siftDown(std::vector<int>& a, int i, int end) {
    int j = leafSearch(a, i, end);

    while (a[i] > a[j]) {
        j = (j - 1) / 2;
    }

    while (j > i) {
        std::swap(a[i], a[j]);
        j = (j - 1) / 2;
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, i, n);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        siftDown(arr, 0, i);
    }
}
//
// void siftUp(int* arr, int index) {
//     if (index == 0) {
//         return;
//     }
//
//     int parentIndex = (index - 1) / 2;
//
//     if(arr[index] > arr[parentIndex]) {
//         std::swap(arr[index], arr[parentIndex]);
//         siftUp(arr, parentIndex);
//     }
// }

int main() {
    std::vector<int> arr = {4, 1, 9, 4, 3, 2, 5, 10, 31, 24};
    int n = arr.size();

    std::cout << "Original array: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    heapSort(arr);

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
