#include "main.h"
#include "connection/clientGreeter.h"
#include "../util/logger.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main() {
    ConnectionManager c;
    ClientGreeter g(&c, 8000);
    g.start_in_new_thread();
    while(true) {
        boost::this_thread::sleep_for(boost::chrono::seconds{1});
        std::string str;
        for (ClientConnection *cc : c.connections) {
            if (!cc->isRunning()) {
                Logger::info("Removing connection (" + cc->getIp() + ")");
                c.removeConnection(cc);
            } else if (cc->isRegisterd()) {
                str += "(" + cc->getIp() + ",\"" + cc->getName() + "\")";
            }
        }
        for (ClientConnection *cc : c.connections) {
            if (cc->isRunning() && cc->isRegisterd()) {
                boost::asio::write(*(cc->getSocket()), boost::asio::buffer(str + "\n"));
            }
        }
    }
    g.wait_for();
}
#pragma clang diagnostic pop