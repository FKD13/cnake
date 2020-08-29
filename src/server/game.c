#include <stdlib.h>
#include <stdio.h>

#include "game.h"

game_t* init_game_t() {
  game_t* game = malloc(sizeof(game_t));
  if (game == NULL) {
    printf("Failed to malloc");
  }
  game->clients = init_list_t();
  return game;
}

void free_game_t(game_t** game) {
  if ((*game)->clients != NULL) {
    free_list_t(&((*game)->clients));
  }
  free(*game);
  *game = NULL;
}

void add_client(game_t* game, client_t* client) {
  add_item(game->clients, (void*) client);
}

void remove_client(game_t* game, client_t* client) {
  remove_item(game->clients, (void*) client);
}
