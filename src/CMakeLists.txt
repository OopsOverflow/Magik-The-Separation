include_directories(backend)

add_subdirectory(backend)

link_libraries(stdc++fs)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(${PROJECT_NAME}_run sfml-audio sfml-graphics sfml-window sfml-system)