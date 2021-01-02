FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update
RUN apt-get install -y build-essential g++ gdb clang clang-format clang-tidy cmake libboost-all-dev libgtest-dev git \
                       nlohmann-json3-dev
RUN cd /usr/src/googletest; mkdir build; cd build; cmake ..; make ; make install
RUN cd /usr/src/; git clone https://github.com/el-bart/but.git; cd but; cd build; cmake .. ; make ; make install