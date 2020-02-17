#include "snake.h"

Snake::Snake() {
    snake.push_front(std::pair<int, int>(0, 0));
}

void Snake::grow(Direction d) {
    snake.push_front(std::pair<int, int>(snake.front()));
    if (d == N) {
        snake.front().second--;
    } else if (d == Z) {
        snake.front().second++;
    } else if (d == W) {
        snake.front().first--;
    } else if (d == O) {
        snake.front().first++;
    }
}

void Snake::move(Direction d) {
    grow(d);
    snake.pop_back();
}

std::string Snake::to_string() {
    std::string s = "[";
    for (std::pair<int, int> p: snake) {
        s += "(" + std::to_string(p.first) + "," + std::to_string(p.second) + ")";
    }
    s += "]";
    return s;
}