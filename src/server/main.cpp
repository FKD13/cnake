#include "main.h"
#include "connection/clientGreeter.h"

int main() {
    ConnectionManager c;
    ClientGreeter g(&c, 8000);
    g.start_in_new_thread();
    g.wait_for();
}