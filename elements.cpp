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

connection::connection(int delay_time){
    this->delay = delay_time;
    this->packet_sent = 0;
    this->packet_received = 0;
    this->hold_delay = delay_time;
    this->buffer = 0;
}

void connection::send(){
    this->packet_sent++;
    if(this->delay > 0){
       this->delay--;
       this->buffer = 0;
    }else{
        this->buffer = 1;
        this->delay = this->hold_delay;
    }

}


uint8_t connection::receive(void){
    uint8_t data;
    data = this->buffer;
    if(this->buffer > 0){
        this->buffer = 0;
        this->packet_received++;
    }


    return data;
}
