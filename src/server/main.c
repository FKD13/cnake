#include "socket.h"

int main() {
    server_t server;

    server.config.sin_family = AF_INET;
    server.config.sin_addr.s_addr = INADDR_ANY;
    server.config.sin_port = htons(8888);

    server_start(&server);
}