cmake_minimum_required(VERSION 2.8.12)
project(cnake)

# Client configuration
add_executable(cnake src/client/snake.c)

target_link_libraries(cnake ncurses)

# Server configuration
add_executable(server
        src/server/main.cpp
        src/server/connection/clientConnection.cpp
        src/server/connection/clientGreeter.cpp
        src/server/connection/connectionManager.cpp
        src/util/Threadable.cpp
        src/util/logger.cpp
        src/server/snake.cpp src/server/game.cpp src/server/game.h)

target_link_libraries(server boost_system)
target_link_libraries(server boost_thread)
target_link_libraries(server boost_chrono)
target_link_libraries(server pthread)