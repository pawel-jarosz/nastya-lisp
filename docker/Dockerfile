FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive
ARG USER_ID
ARG GROUP_ID

RUN apt-get update
RUN apt-get install -y build-essential g++ gdb clang clang-format clang-tidy cmake libboost-all-dev libgtest-dev git \
                       nlohmann-json3-dev librange-v3-dev
RUN cd /usr/src/googletest; mkdir build; cd build; cmake ..; make ; make install
RUN cd /usr/src/; git clone https://github.com/el-bart/but.git; cd but; cd build; cmake .. ; make ; make install

RUN rm /var/lib/dpkg/lock
RUN apt-get install -y librange-v3-dev

RUN mkdir -p /home/builder
RUN groupadd builder
RUN useradd -r -u $USER_ID -g builder builder
RUN chown builder:builder /home/builder
USER builder
