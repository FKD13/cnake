#include "main.h"
#include "connection/clientGreeter.h"

int main() {
    ConnectionManager c;
    ClientGreeter g(&c, 8000);
    g.start_in_new_thread();
    while(true) {
        boost::this_thread::sleep_for(boost::chrono::seconds{1});
        for (ClientConnection *cc : c.connections) {
            if (cc->isRunning() && cc->isRegisterd()) {
                std::cout << cc->getName() << ": " << std::to_string(cc->getLastDir()) << std::endl;
            }
        }
    }
    g.wait_for();
}