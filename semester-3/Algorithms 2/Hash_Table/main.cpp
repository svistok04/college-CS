//ALGO2 IS1 223A LAB06
//Vladyslav Zosimchuk
//zv53855@zut.edu.pl

#include <iostream>
#include <sstream>
#include <random>
#include "DynamicArray.hpp"
#include "LinkedList.hpp"

template<typename T>
class HashTable {
    DynamicArray<T>* da;

public:
    HashTable() : da(new DynamicArray<T>()) {}
    ~HashTable() {
        delete da;
    }
    void addNewElement(const std::string&, const T&); // a
    std::string findElement(const std::string&); // b
    bool removeElement(const std::string&); // c
    void clearHT(); // d
    std::string chain_to_string(LinkedList<T>*&, int);
    std::string HT_to_string(); // e
    int hash_function(const std::string&); // f
    void rehash_function(); // g
};

std::string randomKey(int);

int main() {
    const int MAX_ORDER = 5;
    HashTable<int> myHT;
    for (int o = 1; o <= MAX_ORDER; ++o) {
        const int n = pow(10, o);
        clock_t t = clock();
        for (int i = 0; i < n; ++i) {
            myHT.addNewElement(randomKey(6), i);
        }
        std::cout << myHT.HT_to_string();
        std::cout << "It took " << static_cast<float>(clock() - t) / CLOCKS_PER_SEC * 1000 << " ms to attempt to add "
        << n << " objects to a hash table" << std::endl;
        myHT.clearHT();
    }

    // HashTable<int> myHT;
    // myHT.addNewElement("keey", 123);
    // myHT.addNewElement("qwerty", 193);
    // myHT.addNewElement("azerty", 93);
    // myHT.addNewElement("jre", 3210);
    // myHT.addNewElement("random", 12343546);
    // myHT.addNewElement("reg", 32);
    // myHT.addNewElement("sdvfd", 12);
    // myHT.addNewElement("24t35gte", 0);
    // myHT.addNewElement("ewk", 10);
    // myHT.addNewElement("wer", 22);
    // myHT.addNewElement("wew", 42);
    // myHT.addNewElement("ewrerefw", 2222);
    // myHT.addNewElement("wefretxd", 1111111111);
    // std::cout << myHT.findElement("azerty");
    // std::cout << myHT.findElement("rgorej");
    // std::cout << myHT.HT_to_string();
    // std::cout << myHT.removeElement("jre");
    // myHT.addNewElement("qwerty", 1234);
    // std::cout << myHT.HT_to_string();
    // std::cout << myHT.removeElement("qwerty");
    // std::cout << myHT.HT_to_string();
    // myHT.clearHT();
    // std::cout << myHT.HT_to_string();
    return 0;
}

template<typename T>
void HashTable<T>::addNewElement(const std::string& key, const T& value) {
    if ((double)da->sizePairs / da->capacity >= da->capacityLimit) rehash_function();
    int index = hash_function(key);
    if (!da->arr[index]) {
        da->arr[index] = new LinkedList<T>(key, value);
        ++da->sizeLists;
    } else {
        auto* traverser = da->arr[index];
        while (traverser) {
            if (traverser->key == key) {
                traverser->value = value;
                return;
            }
            if (traverser->next == nullptr) {
                traverser->next = new LinkedList<T>(key, value);
                ++da->sizePairs;
                return;
            }
            traverser = traverser->next;
        }
    }
    ++da->sizePairs;
}

template<typename T>
std::string HashTable<T>::findElement(const std::string& key) {
    std::stringstream ss;
    int index = hash_function(key);
    bool found = false;
    if (da->arr[index]) {
        auto* traverser = da->arr[index];
        while (traverser) {
            if (traverser->key == key) {
                ss << index << ": " << traverser->key << " -> " << traverser->value << ";" << std::endl;
                found = true;
                break;
            }
            traverser = traverser->next;
        }
    }
    if (!found) ss << "NULL" << std::endl;
    return ss.str();
}
template<typename T>
bool HashTable<T>::removeElement(const std::string& key) {
    int index = hash_function(key);
    if (da->arr[index]) {
        if (da->arr[index]->key == key) {
            auto* current = da->arr[index];
            da->arr[index] = da->arr[index]->next;
            delete current;
            --da->sizePairs;
            if (!da->arr[index]) --da->sizeLists;
            return true;
        }
            auto *prev = da->arr[index];
            auto *current = da->arr[index]->next;
            while (current) {
                if (current->key == key) {
                    prev->next = current->next;
                    delete current;
                    --da->sizePairs;
                    return true;
                }
                prev = current;
                current = current->next;
            }
    }
    return false;
}


template<typename T>
void HashTable<T>::clearHT() {
    auto* newDA = new DynamicArray<T>;
    std::fill_n(newDA->arr, newDA->capacity, nullptr);
    delete da;
    da = newDA;
}

template<typename T>
std::string HashTable<T>::chain_to_string(LinkedList<T>*& chain, int index) {
    std::stringstream ss;
    ss << "       " << index << ": ";
    auto* traverser = chain;
    while (traverser) {
        ss << traverser->key << " -> " << traverser->value;
        (traverser->next) ? ss << ", " : ss << ";";
        traverser = traverser->next;
    }
    return ss.str();
}

template<typename T>
std::string HashTable<T>::HT_to_string() {
    std::stringstream ss;
    int minListSize{9999999};
    int maxListSize{};
    ss << "hash table: " << std::endl
    << "  current number of pairs: " << da->sizePairs << std::endl
    << "  capacity: " << da->capacity << std::endl
    << "  table: " << std::endl
    << "  {" << std::endl;
    int x{};
    for (int i = 0; i < da->capacity; ++i) {
        if(da->arr[i]) {
            auto* traverser = da->arr[i];
            int size{};
            while (traverser) {
                ++size;
                traverser = traverser->next;
            }
            if (size < minListSize) minListSize = size;
            if (size > maxListSize) maxListSize = size;
            if (x < 10) {
                ss << chain_to_string(da->arr[i], i) << std::endl;
            }
            ++x;
        }
    }
    if (minListSize == 9999999) minListSize = 0;
    if (x > 10) ss << "       ..." << std::endl;
    ss << "  }" << std::endl
    << "  stats:" << std::endl
    << "    list min size: " << minListSize << std::endl
    << "    list max size: " << maxListSize << std::endl
    << "    non-null lists: " << da->sizeLists << std::endl
    << "    list avg size: " << static_cast<double>(da->sizePairs) / static_cast<double>(da->sizeLists) << std::endl;
    ;
    return ss.str();
}

template<typename T>
int HashTable<T>::hash_function(const std::string& key) {
    int value{};
    int i{1};
    size_t length = key.length();
    for (const char ch : key) {
        value += pow(ch, (length)-i) * 31;
        ++i;
    }
    value %= da->capacity;
    return value >= 0 ? value : value + da->capacity;
}

template<typename T>
void HashTable<T>::rehash_function() {
    int oldCapacity = da->capacity;
    da->capacity *= 2;
    auto** newArr = new LinkedList<T>*[da->capacity]();
    for (int i = 0; i < oldCapacity; ++i) {
        if (da->arr[i]) {
            auto* element = da->arr[i];
            int index = hash_function(element->key);
            newArr[index] = new LinkedList<T>(element->key, element->value);
            while (element) {
                auto* tmp = element;
                element = element->next;
                delete tmp;
            }
        }
    }
    delete[] da->arr;
    da->arr = newArr;
}

std::string randomKey(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);
    std::string key;

    for (int i = 0; i < length; ++i) {
        key += 'a' + dis(gen);
    }

    return key;
}
