cmake_minimum_required(VERSION 3.24)
project(lab4_new)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Forest)
add_subdirectory(Tree)
add_subdirectory(Tree_old)

add_executable(lab4_new main.cpp)

target_link_libraries(lab4_new PRIVATE Forest)
target_link_libraries(lab4_new PRIVATE Tree)
target_link_libraries(lab4_new PRIVATE Tree_old)

