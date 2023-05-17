cmake_minimum_required(VERSION 3.25)
project(lab10)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Player)

add_executable(lab10 main.cpp)

target_link_libraries(lab10 PRIVATE Player)