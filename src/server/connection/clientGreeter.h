#ifndef CNAKE_CLIENTGREETER_H
#define CNAKE_CLIENTGREETER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>

class ClientGreeter {
private:
    int port;
    int socketDescriptor;
public:
    explicit ClientGreeter(int port);
    ~ClientGreeter();
    void run();
};

#endif //CNAKE_CLIENTGREETER_H
