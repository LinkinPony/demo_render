cmake_minimum_required(VERSION 3.21)
project(demo_render)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS “-Wall -Wextra”)
#set(CMAKE_CXX_FLAGS_DEBUG “-g”)
#set(CMAKE_CXX_FLAGS “-pthread”)
set(CMAKE_CXX_FLAGS_RELEASE “-O2”)
set(SOURCE_FILES main.cpp)

include_directories(
        .
        include/
        thirdPartyLib/imgui/
        thirdPartyLib/
        GUI/
        thirdPartyLib/stb
)
aux_source_directory(. MAIN_SRC)
aux_source_directory(src CODE_SRC)
aux_source_directory(thirdPartyLib/imgui IMGUI_SRC)
aux_source_directory(thirdPartyLib/imgui/GLFW GLFW_SRC)
aux_source_directory(GUI GUI_SRC)
add_executable(
        demo_render
        ${MAIN_SRC}
        ${CODE_SRC}
        ${IMGUI_SRC}
        ${GLFW_SRC}
        ${GUI_SRC}
        thirdPartyLib/stb/stb_image.h
)

#include_directories(GL)
#Windows: OPENGL32
#Linux: GL
target_link_libraries(demo_render glfw3 GL dl X11 pthread)
