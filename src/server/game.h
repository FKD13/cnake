#ifndef CNAKE_GAME_H
#define CNAKE_GAME_H

#include <stdint.h>

#include "client.h"

#define BLACK_NODE 0
#define RED_NODE 1

typedef struct client_node {
    struct client_node *left;
    struct client_node *right;
    struct client_node *parent;
    uint8_t color;
    client_t *value;
} client_node_t;

typedef struct game {
    int nr_clients;
    client_node_t *root;
} game_t;

int add_client(game_t *game, client_t *client);

void remove_client(game_t *game, client_t *client);

void validate_game_tree(game_t *game, client_node_t *client_node);

client_t **get_all_clients(game_t *game);

#endif //CNAKE_GAME_H
