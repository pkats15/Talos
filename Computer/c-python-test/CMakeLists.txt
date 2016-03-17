cmake_minimum_required(VERSION 3.3)
project(c_python_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES test_c.c)
add_executable(c_python_test ${SOURCE_FILES})