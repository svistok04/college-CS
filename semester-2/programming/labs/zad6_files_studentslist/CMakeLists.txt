cmake_minimum_required(VERSION 3.25)
project(zad6_files_studentslist)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Student)

add_executable(zad6_files_studentslist main.cpp)

target_link_libraries(zad6_files_studentslist PRIVATE Student)