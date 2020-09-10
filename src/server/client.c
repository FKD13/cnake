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
    get(&buf, 12, client);
    printf("%s", buf);
  }
  pthread_exit(NULL);
}

void get(char** buf, int size, client_t* client) {
  int i;
  int done = 0;
  char buff[12] = {0};
  while (done < size) {
    i = recv(client->sock, buf+done, size - done, 0);
    printf("i: %d, done: %d\n", i, done);
    if (i <= 0) {
      /* 0 bytes returned, this means the client left */
      printf("[%d] Client Disconnected\n", client->id);
      pthread_exit(NULL);
    }
    done += i;
  }
  printf("%s\n", *buf);
}

void disconnect() {
    printf("disconnecting client");
}
