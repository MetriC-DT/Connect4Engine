cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_SHARED_LINKER_FLAGS "-fopenmp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Ofast")

project(Connect4Engine)

set(BINARY ${CMAKE_PROJECT_NAME})
set(SRC_LIB src.so)

include_directories(src)
add_subdirectory(src)
add_subdirectory(test)

add_executable(${BINARY} src/main.c)
target_link_libraries(${BINARY} ${SRC_LIB})
