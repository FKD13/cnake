#include "game.h"

Game::Game() : width(100), height(100), apple(1, 1), greeter(&manager, 8000){
    greeter.start_in_new_thread();
}

void Game::run() {
    while (1) {
        clean();
        step();
        send_report();
        boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    }
}

void Game::send_report() {
    std::string str;
    for (ClientConnection *cc: manager.connections) {
        if (cc->isRegisterd() && cc->isRunning()) {
            str += "(" + cc->getName() + cc->getSnake().to_string() + ")";
        }
    }
    for (ClientConnection *cc: manager.connections) {
        if (cc->isRegisterd() && cc->isRunning()) {
            cc->write(str);
        }
    }
}

void Game::clean() {
    for (ClientConnection *cc: manager.connections) {
        if (!cc->isRunning()) {
            manager.removeConnection(cc);
        }
    }
}

void Game::step() {
    /* TODO: Check for apple collision */
    for (ClientConnection *cc: manager.connections) {
        if (cc->isRegisterd() && cc->isRunning()) {
            cc->getSnake().move(cc->getLastDir());
        }
    }
}