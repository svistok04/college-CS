cmake_minimum_required(VERSION 3.24)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Forest)
add_subdirectory(Tree)
add_subdirectory(Tree_old)

add_executable(lab4 main.cpp)

target_link_libraries(lab4 PRIVATE Forest)
target_link_libraries(lab4 PRIVATE Tree)
target_link_libraries(lab4 PRIVATE Tree_old)

