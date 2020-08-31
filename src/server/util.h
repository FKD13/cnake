#ifndef CNAKE_SERVER_UTIL_H
#define CNAKE_SERVER_UTIL_H

#include "game.h"
#include "client.h"

typedef struct thread_args {
  client_t* client;
  game_t* game;
} thread_args_t;

#endif //CNAKE_SERVER_UTIL_H
