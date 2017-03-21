cmake_minimum_required(VERSION 3.6)
project(Pinyin)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(SOURCE_FILES main.cpp charset.cpp charset.h spell.cpp spell.h frequency.cpp frequency.h)
add_executable(Pinyin ${SOURCE_FILES})