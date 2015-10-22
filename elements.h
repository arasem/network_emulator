#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <stdint.h>
#include "pthread.h"

class node;
class connection;
class port;

typedef void (node_cb_t)(port *port_p);

class port{
public:
int input_number;
connection **input_p;
int output_number;
connection **output_p;

};

class connection{
    private:
    bool buffer_full;
    uint8_t buffer;
    public:
    bool problem;
    connection(void);
    void send(uint8_t data);
    uint8_t receive(void);
};

class node {


    public:
        char name;
        bool problem;
        pthread_t thread;
        port *port_p;
        node_cb_t *cb;
        void behaviour(port *port_p);
        node(void);
        int ms_interaction_time;
        bool continious;

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

