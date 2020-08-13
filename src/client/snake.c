#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "display.h"

void connect_to_server(int *sock, struct sockaddr_in *addr) {
    if (((*sock) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("Could not create socket\n");
        exit(1);
    }
    if (connect(*sock, (struct sockaddr *) addr, sizeof(*addr)) < 0) {
        printf("Could not connect to server\n");
        exit(1);
    }
}

int main(int argc, const char *argv[]) {
    int socket = 0;
    struct sockaddr_in server;

    /* Initialize sockaddr_in with correct values */
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    connect_to_server(&socket, &server);

    display_t dp;

    init_display(&dp);

    caca_set_display_title(dp.display, "Hello!");
    caca_set_color_ansi(dp.canvas, CACA_BLACK, CACA_WHITE);
    caca_put_str(dp.canvas, 0, 0, "This is a message");
    caca_refresh_display(dp.display);

    free_display(&dp);

    return 0;
}