cmake_minimum_required(VERSION 3.24)
project(lab6_lab4)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Forest)
add_subdirectory(Tree)
add_subdirectory(Tree_old)
add_subdirectory(Shape)
add_subdirectory(RightTriangle)
add_subdirectory(Border)
add_subdirectory(Rectangle)
add_subdirectory(Triangle)

add_executable(lab6_lab4 main.cpp)

target_link_libraries(lab6_lab4 PRIVATE Forest)
target_link_libraries(lab6_lab4 PRIVATE Tree)
target_link_libraries(lab6_lab4 PRIVATE Tree_old)
target_link_libraries(lab6_lab4 PRIVATE Shape)
target_link_libraries(lab6_lab4 PRIVATE RightTriangle)
target_link_libraries(lab6_lab4 PRIVATE Border)
target_link_libraries(lab6_lab4 PRIVATE Rectangle)
target_link_libraries(lab6_lab4 PRIVATE Triangle)