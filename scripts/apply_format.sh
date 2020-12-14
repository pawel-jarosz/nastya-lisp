#!/usr/bin/sh

find .. -name "*.hpp" -o -name "*.cpp" -exec clang-format -i {} \;
