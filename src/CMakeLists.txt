set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_custom_command(TARGET ${BINARY}_run
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}_run> ../../)

add_library(${BINARY}_lib STATIC ${SOURCES} backend/components/type/Color.h)