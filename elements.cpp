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
