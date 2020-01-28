#ifndef CNAKE_CLIENTCONNECTION_H
#define CNAKE_CLIENTCONNECTION_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
#include "../../util/move.h"

class ClientConnection {
private:
    boost::asio::ip::tcp::socket *socket;
    boost::thread *thread = nullptr;
    Direction last_dir;
public:
    ClientConnection(boost::asio::ip::tcp::socket *socket);
    ~ClientConnection();
    static void run(ClientConnection *c);
    void activate();
};

#endif //CNAKE_CLIENTCONNECTION_H
