cmake_minimum_required(VERSION 3.25)
project(lab6)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Game)
add_subdirectory(Player)
add_subdirectory(Wheel)

add_executable(lab6 main.cpp)

target_link_libraries(lab6 PRIVATE Game)
target_link_libraries(lab6 PRIVATE Player)
target_link_libraries(lab6 PRIVATE Wheel)
