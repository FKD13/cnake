#ifndef CNAKE_THREADABLE_H
#define CNAKE_THREADABLE_H


#include <boost/thread.hpp>

class Threadable {
protected:
    boost::thread *thread = nullptr;
    bool running = true;
    virtual void run();
public:
    Threadable() = default;
    virtual ~Threadable();
    static void start(Threadable *t);
    void start_in_new_thread();
    void wait_for();
};


#endif //CNAKE_THREADABLE_H
