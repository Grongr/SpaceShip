cmake_minimum_required(VERSION 3.16)
project(SpaceShip VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(spaceship main.cpp spaceship.cpp spaceship.h unitests.h unitests.cpp)