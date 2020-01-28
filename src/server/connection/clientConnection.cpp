/**
 * This class will handle an existing connection with a client.
 **/

#include "clientConnection.h"

ClientConnection::ClientConnection(boost::asio::ip::tcp::socket *socket) : socket(socket), last_dir(N) {}

ClientConnection::~ClientConnection() {
    if (thread != nullptr) {
        thread->interrupt();
        delete thread;
        thread = nullptr;
    }
    delete socket;
    socket = nullptr;
}

/* static */
void ClientConnection::run(ClientConnection *c) {
    while (true) {
        boost::asio::streambuf buf;
        boost::asio::read_until(*(c->socket), buf, '\n');
        std::cout << boost::asio::buffer_cast<const char *>(buf.data());
    }
}

void ClientConnection::activate() {
    thread = new boost::thread{[this](){ClientConnection::run(this);}};
}