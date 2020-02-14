/**
 * This class will handle an existing connection with a client.
 **/

#include <string>
#include "clientConnection.h"

ClientConnection::ClientConnection(boost::asio::ip::tcp::socket *socket) : socket(socket), last_dir(N), registered(false) {}

ClientConnection::~ClientConnection() {
    socket->close();
    socket->release();
    delete socket;
    socket = nullptr;
}

void ClientConnection::run() {
    reg();
    while (running) {
        boost::asio::streambuf recv_buff;
        boost::system::error_code err;
        boost::asio::read_until(*socket, recv_buff, '\n', err);
        if (err && err == boost::asio::error::eof) {
            running = false;
        } else {
            Direction newDir = parseDir(std::string(boost::asio::buffer_cast<const char*>(recv_buff.data())));
            if (newDir != WRONG) {
                last_dir = newDir;
            } else {
                boost::asio::write(*socket, boost::asio::buffer("BYE\n"));
                running = false;
            }
        }
    }
}

void ClientConnection::reg() {
    boost::asio::streambuf recv_buff;
    boost::system::error_code err;

    boost::asio::write(*socket, boost::asio::buffer("IDENTIFY\n"));
    boost::asio::read_until(*socket, recv_buff, '\n', err);
    name = std::string(boost::asio::buffer_cast<const char*>(recv_buff.data()));
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    if (name.empty()) {
        reg();
    }
    registered = true;
}

Direction ClientConnection::parseDir(const std::string s) {
    if (s == "N\n") return N;
    else if (s == "Z\n") return Z;
    else if (s == "W\n") return W;
    else if (s == "O\n") return O;
    else return WRONG;
}

Direction ClientConnection::getLastDir() const {
    return last_dir;
}
