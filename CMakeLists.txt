cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "MAGIK")
project(${PROJECT_NAME})

#set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML/lib/cmake/SFML")

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_subdirectory(src)