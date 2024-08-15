cmake_minimum_required(VERSION 3.24)

project(From_Java_to_Cplusplus-Naming-Files)

set(CMAKE_CXX_STANDARD 14)

# Files from `./src` directory
set(HEADERS
        src/point.hpp)
set(SRC
        src/main.cpp
        src/point.cpp)


# Running learner side code
# Use PROJECT_NAME dependent names of targets for the plugin support to work correctly.
add_executable(${PROJECT_NAME}-run ${SRC} ${HEADERS})