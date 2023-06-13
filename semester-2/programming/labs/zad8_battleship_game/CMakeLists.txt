cmake_minimum_required(VERSION 3.25)
project(zad8_battleship_game)

set(CMAKE_CXX_STANDARD 23)

add_executable(zad8_battleship_game main.cpp Board/Board.cpp Board/Board.hpp Computer/Computer.cpp Computer/Computer.hpp Game/Game.cpp Game/Game.hpp Player/Player.cpp Player/Player.hpp Ships/Ship.cpp Ships/Ship.hpp)

add_subdirectory(
        Ships
)
add_subdirectory(
        Game
)
add_subdirectory(
        Board
)
add_subdirectory(
        Player
)
add_subdirectory(
        Computer
)


target_link_libraries(zad8_battleship_game PRIVATE Ships)
target_link_libraries(zad8_battleship_game PRIVATE Game)
target_link_libraries(zad8_battleship_game PRIVATE Board)
target_link_libraries(zad8_battleship_game PRIVATE Player)
target_link_libraries(zad8_battleship_game PRIVATE Computer)
target_link_libraries(zad8_battleship_game PRIVATE ncurses)

