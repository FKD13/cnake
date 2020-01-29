#ifndef CNAKE_CLIENTGREETER_H
#define CNAKE_CLIENTGREETER_H

#include "connectionManager.h"

class ClientGreeter : public Threadable {
private:
    boost::asio::io_service *io_service;
    boost::asio::ip::tcp::acceptor *acceptor;
    ConnectionManager *manager;
    void run() override;
public:
    explicit ClientGreeter(ConnectionManager *manager, int port);
    ~ClientGreeter() override;
};

#endif //CNAKE_CLIENTGREETER_H
