#!/bin/sh

pushd ../docker
USER_ID=$(id -u $USER)
GROUP_ID=$(id -g $USER)

docker build --build-arg USER_ID=$USER_ID --build-arg GROUP_ID=$GROUP_ID -t nastya-builder .

popd