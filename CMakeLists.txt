cmake_minimum_required (VERSION 3.5)
set(PROJECT_NAME "MAGIK")
project(${PROJECT_NAME})
# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS ON)

# Enable all compiler warnings
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

# Link against pthreads under Unix systems
if (NOT MSVC AND NOT MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# Under MinGW, statically link against the standard libraries
if (MINGW)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Force WebSocket++ to use 100% C++11 mode, so that it doesn't try to look for Boost
# (Note that under MinGW, Boost.Thread is still required, due to a bug in MinGW that prevents the C++11 version from being used)
add_definitions(-D_WEBSOCKETPP_CPP11_STRICT_)

# Add the third-party headers directory to the search path
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/libs")

add_subdirectory(src)

include_directories(src)


