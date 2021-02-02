#!/bin/bash

pushd ..
docker run -v $PWD:/home/builder/sources \
           -it nastya-builder:latest bash -c "cd /home/builder/sources/build; cmake ..; make all; make test"
popd
