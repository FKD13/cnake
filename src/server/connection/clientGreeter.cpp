/**
 * This class will handle new clients connecting, and create the according clientConnection.
 **/

#include <iostream>
#include "clientGreeter.h"

ClientGreeter::ClientGreeter(ConnectionManager *manager, int port) : manager(manager){
    io_service = new boost::asio::io_service();
    acceptor = new boost::asio::ip::tcp::acceptor(
            *io_service,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port )
            );
}

ClientGreeter::~ClientGreeter() {}

void ClientGreeter::run() {
    while (true) {
        auto *socket = new boost::asio::ip::tcp::socket(*io_service);
        acceptor->accept(*socket);
        manager->addConnection(new ClientConnection(socket))->activate();
        std::cout << "Client connected" << std::endl;
    }
}