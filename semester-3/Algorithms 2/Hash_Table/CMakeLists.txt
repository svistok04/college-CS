cmake_minimum_required(VERSION 3.26)
project(Hash_Table)

set(CMAKE_CXX_STANDARD 23)

add_executable(Hash_Table main.cpp
        DynamicArray.hpp
        LinkedList.hpp)
