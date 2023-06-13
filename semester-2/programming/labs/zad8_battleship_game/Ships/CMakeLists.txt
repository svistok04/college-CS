cmake_minimum_required(VERSION 3.25)
project(zad8_battleship_game)

set(CMAKE_CXX_STANDARD 23)

add_library(
        Ships
        Ship.cpp
        Ship.hpp
        ShipManager.cpp ShipManager.hpp)