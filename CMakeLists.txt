cmake_minimum_required(VERSION 3.1)
project(project)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(project main.cpp src/field.cpp src/snake.cpp src/fruit.cpp game.h src/score.cpp)

target_link_libraries(project sfml-graphics sfml-audio)
