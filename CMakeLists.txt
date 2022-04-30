cmake_minimum_required(VERSION 3.21)
project(demo_render)
set(CMAKE_CXX_STANDARD 20)
add_executable(demo_render
        main.cpp
        include/tgaimage.h
        src/tgaimage.cpp
        include/drawer.h src/drawer.cpp)