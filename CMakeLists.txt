cmake_minimum_required(VERSION 3.22)
project(magik)

set(CMAKE_CXX_STANDARD 20)


# Find SFML shared libraries
find_package(SFML 2.5
        COMPONENTS
        system window graphics network audio REQUIRED
        )

include_directories(src)

add_subdirectory(src)

# Set include directory search paths
target_include_directories(magik
        PRIVATE
        "${PROJECT_BINARY_DIR}"
        )

# Link executable to required SFML libraries
target_link_libraries(magik sfml-graphics)

# Install target
install(TARGETS magik DESTINATION bin)
