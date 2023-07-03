cmake_minimum_required(VERSION 3.0)

project(MyProject)

set(CMAKE_CXX_STANDARD 11)

add_executable( diary diary.cpp pdremove.h pdremove.cpp pdadd.h pdadd.cpp pdlist.cpp pdlist.h pdshow.cpp pdshow.h)