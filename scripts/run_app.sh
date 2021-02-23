#!/bin/bash

pushd ..
docker run -v $PWD:/home/builder/sources \
           -it nastya-builder:latest bash -c "cd /home/builder/sources/build/bin/; ./nastya-cli"
popd

