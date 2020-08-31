#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#include "client.h"

#include "util.h"

void* handle_connection(void* arg) {
  printf("handling new connection\n");
  thread_args_t* args = (thread_args_t*) arg;
  
  client_t* client = args->client;
  game_t* game = args->game;
  
  /* free the argument again */
  free(arg);
  arg = NULL;
  args = NULL;

  while(game->running) {
    char buf[12] = {0};
    if(recv(client->sock, buf, 12, 0) > 0) {
      printf("[%d] %s", client->id, buf);
    } else {
      pthread_exit(NULL);
    }
  }
  pthread_exit(NULL);
}
