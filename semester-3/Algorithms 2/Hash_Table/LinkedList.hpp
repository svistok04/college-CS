//
// Created by marling on 11/26/23.
//

#ifndef HASH_TABLE_LINKEDLIST_HPP
#define HASH_TABLE_LINKEDLIST_HPP

#include <string>
#include <utility>

template<typename V>
struct LinkedList {
    std::string key;
    V value;
    LinkedList<V>* next;
    LinkedList() = default;
    LinkedList(std::string _key, const V& _value) : key(std::move(_key)), value(_value), next(nullptr) {}
    ~LinkedList() = default;
};


#endif //HASH_TABLE_LINKEDLIST_HPP
