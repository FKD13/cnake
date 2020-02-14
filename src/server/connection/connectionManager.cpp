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

void ConnectionManager::removeConnection(class ClientConnection *c) {
    auto it = connections.begin();
    while (it != connections.end()) {
        if (*it == c) {
            it = connections.erase(it);
        } else {
            it++;
        }
    }
}