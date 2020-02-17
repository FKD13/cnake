/**
 * This class will handle an existing connection with a client.
 **/

#include <string>
#include "clientConnection.h"
#include "../../util/logger.h"

ClientConnection::ClientConnection(boost::asio::ip::tcp::socket *socket) : socket(socket), last_dir(N), registered(false) {
    ip = socket->remote_endpoint().address().to_string();
}

ClientConnection::~ClientConnection() {
    socket->close();
    socket->release();
    delete socket;
    socket = nullptr;
}

void ClientConnection::run() {
    reg();
    while (running) {
        Direction newDir = parseDir(read());
        if (running) {
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
    boost::asio::write(*socket, boost::asio::buffer("IDENTIFY\n"));
    name = read();
    if (name.empty() || !running) {
        Logger::info("Client (" + ip + ") Reqistration Failed");
        running = false;
    } else {
        Logger::info("Client (" + ip + ") Registered");
        registered = true;
    }
}

std::string ClientConnection::read() {
    boost::asio::streambuf recv_buff;
    boost::system::error_code err;
    boost::asio::read_until(*socket, recv_buff, '\n', err);
    if (err && err == boost::asio::error::eof) {
        Logger::warn("Connection dropped (" + ip + "): " + err.message());
        running = false;
        return "";
    }
    else if (err) {
        Logger::warn("Connection dropped (" + ip + "): " + err.message());
        running = false;
        return "";
    } else {
        std::string data = std::string(boost::asio::buffer_cast<const char *>(recv_buff.data()));
        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
        return data;
    }
}

Direction ClientConnection::parseDir(const std::string& s) {
    if (s == "N") return N;
    else if (s == "Z") return Z;
    else if (s == "W") return W;
    else if (s == "O") return O;
    else return WRONG;
}

Direction ClientConnection::getLastDir() const {
    return last_dir;
}
