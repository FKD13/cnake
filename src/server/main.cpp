#include "main.h"
#include "connection/clientGreeter.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main() {
    ConnectionManager c;
    ClientGreeter g(&c, 8000);
    g.start_in_new_thread();
    while(true) {
        boost::this_thread::sleep_for(boost::chrono::seconds{1});
        for (ClientConnection *cc : c.connections) {
            if (cc->isRegisterd()) {
                std::cout << cc->getName() << ": " << std::to_string(cc->getLastDir()) << std::endl;
            }
            if (!cc->isRunning()) {
                std::cout << "removing connection\n";
                c.removeConnection(cc);
            }
        }
    }
    g.wait_for();
}
#pragma clang diagnostic pop