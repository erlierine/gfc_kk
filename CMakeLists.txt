cmake_minimum_required(VERSION 3.7)
project(gfc_kk)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        graph.cpp
        graph.hpp)

add_executable(gfc_kk ${SOURCE_FILES})

