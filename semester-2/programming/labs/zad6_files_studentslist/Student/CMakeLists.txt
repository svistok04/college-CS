cmake_minimum_required(VERSION 3.24)
project(zad6_files_studentslist)

set(CMAKE_CXX_STANDARD 17)

add_library(
        Student
        Student.cpp
        Student.hpp
)