#ifndef CNAKE_CLIENTCONNECTION_H
#define CNAKE_CLIENTCONNECTION_H

#include <boost/asio.hpp>
#include "../../util/move.h"

class ClientConnection {
private:
    Direction lastDir;
    int socketDescriptor;
public:
    explicit ClientConnection(int socketDecriptor);
    ~ClientConnection();
    void run();
};

#endif //CNAKE_CLIENTCONNECTION_H
