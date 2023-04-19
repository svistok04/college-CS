cmake_minimum_required(VERSION 3.25)
project(lab6_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab6_test main.cpp Game.cpp Game.h++)

add_subdirectory(Player)
add_subdirectory(Wheel)

target_link_libraries(lab6_test PRIVATE Player)
target_link_libraries(lab6_test PRIVATE Wheel)