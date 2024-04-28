//ALGO2 IS1 223A LAB07
//Vladyslav Zosimchuk
//zv53855@zut.edu.pl

#include <iostream>
#include <random>
#include <sstream>
#include <ctime>

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

struct Student {
    int index;
    int grade;
    static int studentKeyFunc(const Student& student) {
        return student.grade;
    }
    static bool studentCompFunc(const Student& student1, const Student& student2) {
        return student1.grade > student2.grade;
    }
    bool operator>(const Student& other) const {
        return grade > other.grade;
    }
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << student.index << " " << student.grade;
        return os;
    }
};

void countingSort(int*, int, int);
template<typename T>
void bucketSort(T*, int, int, int(*)(const T&), bool(*)(const T&, const T&));
void bucketSort(int*, int, int);
template<typename T>
bool arraysCompare(T*, T*, int);
template<typename T>
std::string print(T*, int);
int getRandomInRange(int, int);

int main() {
    const int MAX_ORDER = 6;
    for (int o = 1; o <= MAX_ORDER; ++o) {
        const int n = static_cast<int>(pow(10, o));
        std::cout << n << " elements" << std::endl;
        int* array1 = new int[n];
        for (int i = 0; i < n; ++i) {
            array1[i] = getRandomInRange(0, n*10);
        }
        int* array2 = new int[n];
        int* array3 = new int[n];
        int* array4 = new int[n];
        std::copy_n(array1, n, array2);
        std::copy_n(array1, n, array3);
        std::copy_n(array1, n, array4);
        int max = array1[0];
        clock_t t = clock();
        for (int i = 1; i < n; ++i) {
            max = std::max(max, array1[i]);
        }
        countingSort(array1, n, max);
        std::cout << "It took " << static_cast<float>(clock() - t) * 1000 / CLOCKS_PER_SEC << " ms to run counting sort" << std::endl;
        t = clock();
        BinaryHeap<int>* bh1 = new BinaryHeap(array2, n, 0);
        bh1->sort();
        std::cout << "It took " << static_cast<float>(clock() - t) *1000 / CLOCKS_PER_SEC << " ms to run heapsort mode 1" << std::endl;
        t = clock();
        BinaryHeap<int>* bh2 = new BinaryHeap(array3, n, 1);
        bh2->sort();
        std::cout << "It took " << static_cast<float>(clock() - t) * 1000 / CLOCKS_PER_SEC << " ms to run heapsort mode 2" << std::endl;
        t = clock();
        bucketSort(array4, n, n/20 + 1);
        std::cout << "It took " << static_cast<float>(clock() - t) * 1000 / CLOCKS_PER_SEC << " ms to run bucket sort" << std::endl;
        int cmp{};
        cmp += arraysCompare(array1, array2, n) ? 1 : 0;
        cmp += arraysCompare(array2, array3, n) ? 1 : 0;
        cmp += arraysCompare(array3, array4, n) ? 1 : 0;
        // std::cout << print(array1, n);
        (cmp == 3) ? std::cout << "All arrays are sorted correctly\n" : std::cout << "Something is wrong!\n";
        delete bh1;
        delete bh2;
        delete[] array1;
        delete[] array2;
        delete[] array3;
        delete[] array4;
    }

    //
    // int arr1[19] = {4, 1, 9, 4, 3, 2, 5, 10, 31, 24, 12, 541, 1421, 1348, 13, 19, 95241, 0, 34};
    // BinaryHeap<int>* bh1 = new BinaryHeap<int>(arr1, std::size(arr1), 0);
    // bh1->sort();
    // int arr2[19];
    // std::copy_n(arr1, 19, arr2);
    // BinaryHeap<int>* bh2 = new BinaryHeap<int>(arr2, std::size(arr1), 1);
    // bh2->sort();
    // for (const int e : arr1) {
    //     std::cout << e << " ";
    // }
    // std::cout << std::endl;
    // for (const int e : arr2) {
    //     std::cout << e << " ";
    // }
    // std::cout << std::endl;
    // int arr3[] = {4, 1, 9, 4, 3, 2, 5, 10};
    // countingSort(arr3, 8, 10);
    // for (const int e : arr3) {
    //     std::cout << e << " ";
    // }
    // std::cout << std::endl;
    // int arr4[19];
    // std::copy_n(arr1, 19, arr4);
    // countingSort(arr4, 19, 95241);
    // for (const int e : arr4) {
    //     std::cout << e << " ";
    // }
    // std::cout << std::endl;
    // int arr5[19];
    // std::copy_n(arr1, 19, arr5);
    // int arr6[] = {4, 2, 5, 9, 1, 15, 18, 21, 11};
    // bucketSort(arr6, std::size(arr6), 2);
    // bucketSort(arr5, std::size(arr5), 5);
    // for (const int e : arr5) {
    //     std::cout << e << " ";
    // }
    // std::cout << std::endl;
    // for (const int e : arr6) {
    //     std::cout << e << " ";
    // }
    // std::cout << std::endl;
    // Student* arrBucketSort = new Student[10];
    // for (int i = 0; i < 10; ++i) {
    // arrBucketSort[i] = Student(getRandomInRange(11111, 99999), getRandomInRange(0, 100));
    // }
    // Student* arrHeapSort = new Student[10];
    // std::copy_n(arrBucketSort, 10, arrHeapSort);
    // for (int i = 0; i < 10; ++i) {
    //     std::cout << arrBucketSort[i] << std::endl;
    // }
    // std::cout << std::endl;
    // bucketSort(arrBucketSort, 10, 3, Student::studentKeyFunc, Student::studentCompFunc);
    // for (int i = 0; i < 10; ++i) {
    //     std::cout << arrBucketSort[i] << std::endl;
    // }
    // std::cout << std::endl;
    // BinaryHeap<Student>* bh3 = new BinaryHeap(arrHeapSort, 10, 0);
    // bh3->sort();
    // for (int i = 0; i < 10; ++i) {
    //     std::cout << arrHeapSort[i] << std::endl;
    // }
    // delete bh1;
    // delete bh2;
    // delete bh3;
    // delete[] arrBucketSort;
    // delete[] arrHeapSort;
    return 0;
}

void countingSort(int* array, int size, int m) {
    int* output = new int[size]();
    int* count = new int[m+1]();
    // std::fill_n(output, size, 0);
    // std::fill_n(count, m+1, 0);
    for (int i = 0; i < size; ++i) {
        ++count[array[i]];
    }
    for (int i = 1; i <= m; ++i) {
        count[i] += count[i-1];
    }
    for (int i = size - 1; i >= 0; --i) {
        output[count[array[i]] - 1] = array[i];
        --count[array[i]];
    }
    std::copy_n(output, size, array);
    delete[] count;
    delete[] output;
}

template <typename T>
void bucketSort(T* array, int size, int numBuckets, int(*keyFunc)(const T&), bool (*compareFunc)(const T&, const T&)) {
    T** buckets = new T*[numBuckets]();
    int* bucketSizes = new int[numBuckets]();

    T max = array[0];
    for (int i = 1; i < size; ++i) {
        if (compareFunc(array[i], max)) {
            max = array[i];
        }
    }

    for (int i = 0; i < size; ++i) {
        int index = keyFunc(array[i]) * numBuckets / (keyFunc(max) + 1);
        buckets[index] = static_cast<T*>(realloc(buckets[index], (bucketSizes[index] + 1) * sizeof(T)));
        buckets[index][bucketSizes[index]++] = array[i];
    }

    int index = 0;
    for (int i = 0; i < numBuckets; ++i) {
        if (bucketSizes[i] > 0) {
            BinaryHeap<T>* bh = new BinaryHeap(buckets[i], bucketSizes[i], 0);
            bh->sort();
            for (int j = 0; j < bucketSizes[i]; ++j) {
                array[index++] = buckets[i][j];
            }
            delete bh;
        }
        free(buckets[i]);
    }
    delete[] buckets;
    delete[] bucketSizes;
}

void bucketSort(int* array, int size, int numBuckets) {
    int** buckets = new int*[numBuckets]();
    int* bucketSizes = new int[numBuckets]();
    int max = array[0];
    for (int i = 1; i < size; ++i) {
        max = std::max(array[i], max);
    }
    for (int i = 0; i < size; ++i) {
        const unsigned int index = static_cast<unsigned long long>(numBuckets) * array[i] / (max + 1);
        buckets[index] = static_cast<int*>(realloc(buckets[index], (bucketSizes[index] + 1) * sizeof(int)));
        buckets[index][bucketSizes[index]++] = array[i];
    }
    int index = 0;
    for (int i = 0; i < numBuckets; ++i) {
        if (bucketSizes[i] > 0) {
            BinaryHeap<int>* bh = new BinaryHeap(buckets[i], bucketSizes[i], 0);
            bh->sort();
            for (int j = 0; j < bucketSizes[i]; ++j) {
                array[index++] = buckets[i][j];
            }
            delete bh;
        }
        free(buckets[i]);
    }
    delete[] buckets;
    delete[] bucketSizes;
}

template<typename T>
bool arraysCompare(T* array1, T* array2, int size) {
    for (int i = 0; i < size; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
std::string print(T* array, int size) {
    std::stringstream output;
    for (int i = 0; i < size; ++i) {
        output << array[i] << " ";
    }
    output << std::endl;
    return output.str();
}

int getRandomInRange(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}