all: build run

build:
	mkdir -p target
	cd target && cmake ..
	cd target && make

run:
	cd target && ./cnake

docker:
	sudo docker build -t cnake .
	sudo docker run -it cnake --name cnake

