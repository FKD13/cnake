#ifndef CNAKE_CLIENTGREETER_H
#define CNAKE_CLIENTGREETER_H

#include "connectionManager.h"

class ClientGreeter{
private:
    boost::asio::io_service *io_service;
    boost::asio::ip::tcp::acceptor *acceptor;
    ConnectionManager *manager;
public:
    explicit ClientGreeter(ConnectionManager *manager, int port);
    ~ClientGreeter();
    void run();
};

#endif //CNAKE_CLIENTGREETER_H
