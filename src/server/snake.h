#ifndef CNAKE_SNAKE_H
#define CNAKE_SNAKE_H


#include <vector>
#include <string>
#include <list>
#include "../util/move.h"

class Snake {
private:
    std::list<std::pair<int, int>> snake;
public:
    Snake();
    void grow(Direction);
    void move(Direction);
    std::string to_string();
};


#endif //CNAKE_SNAKE_H
