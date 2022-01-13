cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "MAGIK")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

#include(FetchContent)

#FetchContent_Declare(
#        SFML
#        GIT_REPOSITORY https://github.com/SFML/SFML.git
#        GIT_TAG 2.5.1
#)
#FetchContent_MakeAvailable(SFML)

#set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML/lib/cmake/SFML")


add_subdirectory(src)