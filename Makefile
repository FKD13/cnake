all:
	mkdir -p target
	gcc snake.c -o target/snake
	./target/snake

