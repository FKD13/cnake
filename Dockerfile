FROM alpine

RUN apk update && apk add cmake build-base
#RUN apk add pkgconfig
#RUN apk add meson
RUN apk add ncurses-dev
#RUN apk add git
#RUN apk add sudo
#RUN apk add python3-dev
#RUN git clone https://github.com/conan-io/conan.git
#RUN cd conan && sudo pip install -e .


RUN mkdir /cnake
WORKDIR /cnake

COPY snake.c .
COPY Makefile .
COPY CMakeLists.txt .
RUN make build
ENTRYPOINT make run

#COPY meson.build .



#RUN meson target

#WORKDIR /cnake/target
#RUN ninja


#ENTRYPOINT ./cnake
