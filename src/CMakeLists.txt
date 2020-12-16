cmake_minimum_required(VERSION 3.16)
project(nastya_lisp CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_subdirectory(Parser)
add_subdirectory(LispExpression)
add_subdirectory(Tests)
