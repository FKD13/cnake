#include "connectionManager.h"

ConnectionManager::~ConnectionManager() {
    for (ClientConnection *c : connections) {
        delete c;
    }
}

ClientConnection* ConnectionManager::addConnection(ClientConnection *c) {
    connections.push_back(c);
    return c;
}