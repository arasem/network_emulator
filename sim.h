#ifndef SIM_H
#define SIM_H

#include "elements.h"
#include "pthread.h"

class sim{
    private:
        pthread_t thread;
    public:
        sim();
        //bool create(node *node_p);
        bool create(network *network_p);
        bool run(network *network_p);
};



#endif
