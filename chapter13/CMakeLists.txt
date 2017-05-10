cmake_minimum_required(VERSION 3.6)
project(chapter13)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp messageAndFolder.h StrVec.h)
add_executable(chapter13 ${SOURCE_FILES})