cmake_minimum_required(VERSION 3.10)
project(AdvancedTopics_ex4)

set(CMAKE_CXX_STANDARD 14 )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG")


add_executable(AdvancedTopics_ex4 main.cpp ex4_header.h unit_test_util.h)