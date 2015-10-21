#include "iostream"
#include "elements.h"


void node::behaviour(port *port_p){
typedef void func(port *port_p );
    func *f = (func *)this->cb;
    f(this->port_p);

}


node::node(void){
    pthread_t thread1;
    this->thread = thread1;

}

connection::connection(void){
    this->buffer_full = 0;
}

void connection::send(uint8_t data){
    if(this->buffer_full == 0){
        this->buffer = data;
        this->buffer_full = 1;
    }
}


uint8_t connection::receive(void){

    return this->buffer;
}
