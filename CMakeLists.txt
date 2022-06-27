cmake_minimum_required(VERSION 3.21)
project(demo_render)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS “-Wall -Wextra”)
#set(CMAKE_CXX_FLAGS_DEBUG “-g”)
set(CMAKE_CXX_FLAGS_RELEASE “-O3”)
add_executable(demo_render
        main.cpp
        include/tgaimage.h src/tgaimage.cpp
        include/drawer.h src/drawer.cpp
        include/model.h src/model.cpp
        include/geometry.h
        include/matrix.h include/transform.h include/include_all.h src/transform.cpp src/matrix.cpp)