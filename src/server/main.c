#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "socket.h"
#include "game.h"

int main() {
    server_t server;

    server.config.sin_family = AF_INET;
    server.config.sin_addr.s_addr = INADDR_ANY;
    server.config.sin_port = htons(8888);

    game_t* game = init_game_t();
    game->running=1;

    srand(time(NULL));
    
    printf("Starting Socket Server...\n");
    server_start(&server, game);

    free_game_t(&game);
}
