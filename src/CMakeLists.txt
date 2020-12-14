cmake_minimum_required(VERSION 3.19)
project(nastya_lisp CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_subdirectory(Parser)