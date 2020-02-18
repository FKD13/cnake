#ifndef CNAKE_GAME_H
#define CNAKE_GAME_H


#include <utility>
#include "connection/clientConnection.h"
#include "connection/connectionManager.h"
#include "connection/clientGreeter.h"

class Game {
private:
    int width;
    int height;
    std::pair<int, int> apple;
    ConnectionManager manager;
    ClientGreeter greeter;
public:
    Game();
    void run();
    void send_report();
    void clean();
    void step();
    int getWidth() { return width;}
    int getHeigth() { return height;}
    std::pair<int, int>& getApple() { return apple;}
};

#endif //CNAKE_GAME_H
