cmake_minimum_required(VERSION 3.16)
project(nastya_lisp CXX)

set(CMAKE_CXX_STANDARD 17)

include(modules/FindBut.cmake)

enable_testing()
add_subdirectory(src)
