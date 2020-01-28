#include <iostream>

#include "main.h"
#include "connection/clientConnection.h"
#include "connection/clientGreeter.h"

int main() {
    ConnectionManager c;
    ClientGreeter g(&c, 8000);
    g.run();
}