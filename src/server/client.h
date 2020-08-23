#ifndef CNAKE_CLIENT_H
#define CNAKE_CLIENT_H

#include <pthread.h>

typedef struct client {
    pthread_t input_thread;
    int sock;
    int id;
} client_t;

#endif //CNAKE_CLIENT_H
