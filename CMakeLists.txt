cmake_minimum_required(VERSION 3.12)

project(chip8)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    chip8
    chip8.cpp
    Platform.cpp
    beeper.cpp
    main.cpp
)

target_compile_options(chip8 PRIVATE -Wall)

target_link_libraries(chip8 PRIVATE SDL2 GL)