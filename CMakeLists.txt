cmake_minimum_required(VERSION 3.10)

project(TaskC)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(main ${SOURCES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
