#ifndef CNAKE_CLIENTCONNECTION_H
#define CNAKE_CLIENTCONNECTION_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
#include "../../util/move.h"
#include "../../util/Threadable.h"
#include "../snake.h"

class ClientConnection : public Threadable {
private:
    boost::asio::ip::tcp::socket *socket;

    Snake snake;
    Direction last_dir;
    std::string name;
    std::string ip;
    bool registered;

    void run() override;
    Direction parseDir(const std::string&);
    void reg();
public:
    explicit ClientConnection(boost::asio::ip::tcp::socket *socket);
    ~ClientConnection() override;
    Direction getLastDir() const;
    std::string read();
    bool isRegisterd() {return registered;}
    std::string& getName() {return name;}
    std::string& getIp() { return ip;}
    boost::asio::ip::tcp::socket* getSocket() { return socket;}
    Snake& getSnake() { return snake;}
};

#endif //CNAKE_CLIENTCONNECTION_H
