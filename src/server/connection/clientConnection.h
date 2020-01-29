#ifndef CNAKE_CLIENTCONNECTION_H
#define CNAKE_CLIENTCONNECTION_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
#include "../../util/move.h"
#include "../../util/Threadable.h"

class ClientConnection : public Threadable {
private:
    boost::asio::ip::tcp::socket *socket;
    Direction last_dir;
    void run() override;
public:
    explicit ClientConnection(boost::asio::ip::tcp::socket *socket);
    ~ClientConnection() override;
};

#endif //CNAKE_CLIENTCONNECTION_H
