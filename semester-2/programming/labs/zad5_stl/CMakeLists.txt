cmake_minimum_required(VERSION 3.25)
project(zad5_stl)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Team)

add_executable(zad5_stl main.cpp)

target_link_libraries(zad5_stl PUBLIC Team)