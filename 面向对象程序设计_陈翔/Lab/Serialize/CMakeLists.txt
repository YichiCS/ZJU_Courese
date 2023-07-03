cmake_minimum_required(VERSION 3.0)

project(MyProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(akl 
                test.cpp
                tinyxml2.h tinyxml2.cpp
                user_defined_type.h
                binary_test.h binary_serialize.h
                xml_test.h xml_serialize.h
                base64.h base64_test.h base64_serialize.h
                print.h 
                )