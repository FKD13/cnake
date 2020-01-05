/**
 * This class will handle new clients connecting, and create the according clientConnection.
 **/

#include "clientGreeter.h"
#include "clientConnection.h"

ClientGreeter::ClientGreeter(int port) : port(port) {
    socketDescriptor = 0;
}

ClientGreeter::~ClientGreeter() {}

void ClientGreeter::run() {

}