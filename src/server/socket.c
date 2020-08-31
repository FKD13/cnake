#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "socket.h"
#include "client.h"
#include "util.h"

#define CONNECTION_QUEUE 5

/* Start the socket part of the server,
 * 1 = success
 * 0 = failure */
int server_start(server_t* server, game_t* game) {

    if ((server->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        return 0;
    }

    if (bind(server->sock, (struct sockaddr *) &(server->config), sizeof(server->config)) < 0) {
        return 0;
    }

    listen(server->sock, CONNECTION_QUEUE);

    /* start the socket server_config */
    /* TODO */
    server_accept(server, game);

    return 1;
}

_Noreturn void server_accept(server_t* server, game_t* game) {
    /* TODO: replace with proper id's */
    while (1) {
        int _sc_len = sizeof(server->config);
        client_t *client = malloc(sizeof(client_t));
        /* socklen_t -> unsigned int */
        client->sock = accept(server->sock, (struct sockaddr *) &(server->config), (socklen_t *) &_sc_len);
        client->id = rand();
        
        thread_args_t* args = malloc(sizeof(thread_args_t));
        args->client = client;
        args->game = game;

        if (pthread_create(&(client->input_thread), NULL, handle_connection, (void *) args)) {
          printf("Error starting thread\n");
        }
    }
}
