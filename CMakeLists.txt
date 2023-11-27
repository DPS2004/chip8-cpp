cmake_minimum_required(VERSION 3.26)
project(chip8_cpp)

set(CMAKE_CXX_STANDARD 17)


set(SDL2_INCLUDE_DIR C:\\SDL2\\include)
set(SDL2_LIB_DIR C:\\SDL2\\lib\\x64)

#set(IMGUI_INCLUDE_DIR C:/imgui)

include_directories(${SDL2_INCLUDE_DIR})
#include_directories(${IMGUI_INCLUDE_DIR})

link_directories(${SDL2_LIB_DIR})

add_executable(chip8_cpp_graphic main.cpp
        Host.cpp
        Host.h
        Hosts/HostGraphic.cpp
        Hosts/HostGraphic.h
        Chip.cpp
        Chip.h
        font.h
        Display.cpp
        Display.h
)

target_compile_definitions(chip8_cpp_graphic PUBLIC HOST_GRAPHIC)
target_link_libraries(${PROJECT_NAME}_graphic SDL2main SDL2)

add_executable(chip8_cpp_text main.cpp
        Host.cpp
        Host.h
        Hosts/HostText.cpp
        Hosts/HostText.h
        Chip.cpp
        Chip.h
        font.h
        Display.cpp
        Display.h)
target_compile_definitions(chip8_cpp_text PUBLIC HOST_TEXT)
target_link_libraries(${PROJECT_NAME}_text)
