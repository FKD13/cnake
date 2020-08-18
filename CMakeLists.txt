cmake_minimum_required(VERSION 2.8.12)
project(cnake)

# Client configuration
add_executable(cnake src/client/snake.c src/client/display.c src/client/display.h)

target_link_libraries(cnake caca)

# Server configuration
add_executable(server src/server/socket.c src/server/main.c src/server/socket.h src/server/client.c src/server/client.h)

target_link_libraries(server pthread)