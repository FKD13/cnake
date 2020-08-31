#ifndef CNAKE_SOCKET_H
#define CNAKE_SOCKET_H

#include<sys/socket.h>
#include<arpa/inet.h>

#include "game.h"

typedef struct server {
    int sock;
    struct sockaddr_in config;
} server_t;

int server_start(server_t* server, game_t* game);

_Noreturn void server_accept(server_t* server, game_t* game);

#endif //CNAKE_SOCKET_H
