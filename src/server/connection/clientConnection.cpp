/**
 * This class will handle an existing connection with a client.
 **/

#include "clientConnection.h"

ClientConnection::ClientConnection(boost::asio::ip::tcp::socket *socket) : socket(socket), last_dir(N) {}

ClientConnection::~ClientConnection() {
    delete socket;
    socket = nullptr;
}

void ClientConnection::run() {
    while (running) {
        boost::asio::streambuf buf;
        boost::system::error_code err;
        boost::asio::read_until(*socket, buf, '\n', err);
        if (err && err == boost::asio::error::eof) {
            running = false;
        } else {
            std::cout << boost::asio::buffer_cast<const char*>(buf.data());
        }
    }
}