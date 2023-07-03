cmake_minimum_required(VERSION 3.0)

project(MyProject)

set(CMAKE_CXX_STANDARD 11)

add_executable( MyExecutable Adventure.cpp Map.h Map.cpp Game.h Game.cpp)