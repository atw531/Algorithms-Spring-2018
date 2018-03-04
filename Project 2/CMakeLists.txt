cmake_minimum_required(VERSION 3.8)
project(Project_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES travel.cpp Graph.cc Graph.hh)
add_executable(Project_2 ${SOURCE_FILES})