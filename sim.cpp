#include "iostream"
#include "sim.h"
#include "elements.h"
#include "pthread.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

sim::sim(void){



}

void *thread_func(void *node_p){
    std::cout << "thread new \n" << std::endl;


    node *node_ptr = new node;

    node_ptr = (node *) node_p;

    node_ptr->behaviour();

   pthread_exit(NULL);
   }
/*
bool sim::create(node *node_p){

    pthread_create(&(this->thread),NULL, thread_func, (void *) node_p);

    return 0;

};
*/

bool sim::create(network *network_p){

    int counter = 0;

   // pthread_attr_t attr[2];


    for(counter = 0; counter < (network_p->node_number);counter++){
        pthread_create(&(network_p->node_p[counter]->thread),NULL, thread_func, (void *) (network_p->node_p[counter]));

           // test[counter] = pthread_attr_init(&attr[counter]);
    }

    return 0;
}

bool sim::run(network *network_p){


    int counter = 0;
    void *attr[2];
    for(counter = 0; counter < (network_p->node_number);counter++){
        pthread_join(network_p->node_p[counter]->thread,NULL);

    }
    return 0;

}
/*
bool sim::run(){

    pthread_join(this->thread,NULL);

    return 0;
}*/
