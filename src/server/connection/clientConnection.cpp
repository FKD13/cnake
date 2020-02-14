/**
 * This class will handle an existing connection with a client.
 **/

#include <string>
#include "clientConnection.h"

ClientConnection::ClientConnection(boost::asio::ip::tcp::socket *socket) : socket(socket), last_dir(N) {}

ClientConnection::~ClientConnection() {
    socket->close();
    socket->release();
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
            Direction newDir = parseDir(boost::asio::buffer_cast<const std::string>(buf.data()));
            if (newDir != WRONG) {
                last_dir = newDir;
            } else {
                boost::asio::write(*socket, boost::asio::buffer("BYE\n"));
                running = false;
            }
        }
    }
}

Direction ClientConnection::parseDir(const std::string s) {
    switch s {
        case "N": return Z;
        case "O": return N;
        case "Z": return Z;
        case "W": return W;
    }
    return WRONG;
}

Direction ClientConnection::getLastDir() const {
    return last_dir;
}
