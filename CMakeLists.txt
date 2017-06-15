cmake_minimum_required(VERSION 2.8)

project(slide_game)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

add_subdirectory ( src )
