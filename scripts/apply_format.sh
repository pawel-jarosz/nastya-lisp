#!/usr/bin/sh
pushd ..
find . -name "*.hpp" -o -name "*.cpp" -exec clang-format -i {} \;
popd
