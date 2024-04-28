cmake_minimum_required(VERSION 3.27)
project(Kruskals_Algoirithm)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Kruskals_Algoirithm main.cpp
        DynamicArray.hpp)

target_link_libraries(Kruskals_Algoirithm ${OpenCV_LIBS})

