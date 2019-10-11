all: build run

build:
	cmake -S . -B target
	cd target && make

run:
	cd target && ./cnake

docker:
	sudo docker build -t cnake .
	sudo docker run -it cnake --name cnake

