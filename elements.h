#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "pthread.h"

typedef void (*node_cb_t)( void );

class node {


    public:
        char name;
        bool problem;
        pthread_t thread;
        node_cb_t cb;
        void behaviour(void);
        node(void);

};
class connection{

    bool problem;

};


class network{

    public:
        int node_number;
        node **node_p;
        int connection_number;
        connection *connection_p;
        //node queue;

};


#endif

