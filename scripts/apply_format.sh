#!/bin/bash

pushd ..
docker run -v $PWD:/home/builder/sources \
           -it nastya-builder:latest bash -c \
           "cd /home/builder/sources/; find . -name '*.hpp' -o -name '*.cpp' -exec clang-format -i {} \;"
popd
