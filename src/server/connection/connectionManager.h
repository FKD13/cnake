#ifndef CNAKE_CONNECTIONMANAGER_H
#define CNAKE_CONNECTIONMANAGER_H


#include <vector>
#include "clientConnection.h"

class ConnectionManager {
private:
    std::vector<ClientConnection*> connections;
public:
    ~ConnectionManager();
    ClientConnection* addConnection(ClientConnection* c);
};


#endif //CNAKE_CONNECTIONMANAGER_H
