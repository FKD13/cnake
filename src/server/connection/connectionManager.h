#ifndef CNAKE_CONNECTIONMANAGER_H
#define CNAKE_CONNECTIONMANAGER_H


#include <vector>
#include "clientConnection.h"

class ConnectionManager {
public:
    std::vector<ClientConnection*> connections;
    ~ConnectionManager();
    ClientConnection* addConnection(ClientConnection* c);
    void removeConnection(ClientConnection *c);
};


#endif //CNAKE_CONNECTIONMANAGER_H
