cmake_minimum_required(VERSION 3.27)
project(Graham_Scan)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Graham_Scan main.cpp
        DynamicArray.hpp)

target_link_libraries(Graham_Scan ${OpenCV_LIBS})