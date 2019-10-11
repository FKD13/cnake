cmake_minimum_required(VERSION 2.8.12)
project(cnake)

add_executable(cnake snake.c)
target_link_libraries(cnake ncurses)
