cmake_minimum_required(VERSION 3.7)
project(IO_code)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCE_FILES
        main.cpp
        Grupa.cpp
        Konto.cpp
        Klient.cpp
        Trener.cpp
        Kierownik.cpp
        Post.cpp
        Harmonogram.cpp
)

add_executable(IO_code ${SOURCE_FILES})
