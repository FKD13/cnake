#ifndef CNAKE_GAME_H
#define CNAKE_GAME_H

#include <stdint.h>

#include "../util/list.h"
#include "client.h"

typedef struct game {
  list_t* clients;
} game_t;

game_t* init_game_t();
void free_game_t(game_t** game);
void add_client(game_t *game, client_t *client);
void remove_client(game_t *game, client_t *client);

#endif //CNAKE_GAME_H
