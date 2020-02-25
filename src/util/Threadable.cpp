#include "Threadable.h"

Threadable::~Threadable() {
    if (thread != nullptr) {
        running = false;
        thread->join();
        delete thread;
        thread = nullptr;
    }
}

void Threadable::run() {}

/* static */
void Threadable::start(Threadable *t) {
    t->running = true;
    t->run();
}

void Threadable::start_in_new_thread() {
    thread = new boost::thread{[this](){this->start(this);}};
}

void Threadable::wait_for() {
    if (thread != nullptr) {
        thread->join();
    }
}