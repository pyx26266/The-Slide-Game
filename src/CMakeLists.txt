cmake_minimum_required(VERSION 2.8)

project(The-Slide-Game)

add_executable(${PROJECT_NAME} main.cpp game.cxx timer.cxx board.cxx)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
