cmake_minimum_required(VERSION 3.25)
project(zad7_mandelbrot_set)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(zad7_mandelbrot_set main.cpp Fractal.cpp Fractal.hpp)

target_link_libraries(zad7_mandelbrot_set PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
