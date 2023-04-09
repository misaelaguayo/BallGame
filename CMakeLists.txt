cmake_minimum_required(VERSION 3.10)

project(game)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(game game.cpp)

target_link_libraries(game ${SDL2_LIBRARIES})
