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
#include <semaphore.h>

int global_sim = 1;
sem_t sem;
pthread_mutex_t lock;

sim::sim(int ms_time, int ms_resolution){
    int dummy;

    ms_sim_time = ms_time;
    ms_sim_resolution = ms_resolution;

    dummy = (int) (ms_sim_time / ms_sim_resolution);
    event_number = dummy;

}

void *thread_func(void *node_p){
    std::cout << "thread new \n" << std::endl;

    node *node_ptr = new node;

    node_ptr = (node *) node_p;

    node_ptr->behaviour(node_ptr->port_p);

   pthread_exit(0);

   }
/*
bool sim::create(node *node_p){

    pthread_create(&(this->thread),NULL, thread_func, (void *) node_p);

    return 0;

};
*/

bool sim::create(network *network_p){

    int counter = 0;

    for(counter = 0; counter < (network_p->node_number);counter++){
        pthread_create(&(network_p->node_p[counter]->thread),NULL, thread_func, (void *) (network_p->node_p[counter]));


    }

    return 0;
}

bool sim::run(network *network_p){


    event_list **event_array;
    int event_counter = 0,node_counter,counter = 0,event_ = 0;
    int bubble_sort_counter1,bubble_sort_counter2;
    event_array = new event_list *[this->event_number];
    node *temp_node = new node;
    //bubble sort
    for(bubble_sort_counter1 = 0; bubble_sort_counter1<(network_p->node_number -1);bubble_sort_counter1++){
        for(bubble_sort_counter2 = 0; bubble_sort_counter2< ((network_p->node_number)-bubble_sort_counter1 -1); bubble_sort_counter2++){
            if((network_p->node_p[bubble_sort_counter2]->ms_interaction_time) > (network_p->node_p[bubble_sort_counter2+1]->ms_interaction_time)){
                temp_node = network_p->node_p[bubble_sort_counter2];
                network_p->node_p[bubble_sort_counter2] = network_p->node_p[bubble_sort_counter2 + 1];
                network_p->node_p[bubble_sort_counter2 + 1] = temp_node;
            }

        }

    }

    while(this->current_sim_time < this->ms_sim_time){

        for(node_counter = 0; node_counter < network_p->node_number;node_counter++){
            if(network_p->node_p[node_counter]->ms_interaction_time == current_sim_time){
                event_ ++;
                event_array[event_counter] = new event_list;
                event_array[event_counter]->event_number = event_;
                event_array[event_counter]->event_array[event_ - 1]= node_counter;

            }
        }
        event_ = 0;
        event_counter++;
        current_sim_time = current_sim_time + this->ms_sim_resolution;

    }
    current_sim_time = 0;
    for(event_counter = 0; event_counter < this->event_number ; event_counter++){
        if(event_array[event_counter] != NULL){
        std::cout<<"Simulation time" << current_sim_time << "ms \n"<< std::endl;

       if(event_array[event_counter]->event_number == 1){
           network_p->node_p[event_array[event_counter]->event_array[0]]->behaviour(network_p->node_p[event_array[event_counter]->event_array[0]]->port_p);

       }else{
        for(event_ = 0; event_ < event_array[event_counter]->event_number;event_++){
            pthread_create(&(network_p->node_p[event_array[event_counter]->event_array[event_]]->thread),NULL, thread_func, (void *) (network_p->node_p[event_array[event_counter]->event_array[event_]]));
        }
        for(event_ = 0; event_ < event_array[event_counter]->event_number;event_++){
            pthread_join((network_p->node_p[event_array[event_counter]->event_array[event_]]->thread),NULL);
        }
        }

        }
        global_sim = 1;
        current_sim_time = current_sim_time + this->ms_sim_resolution;

    }


    while(1){
        sleep(1);

    }
    return 0;

}
/*
bool sim::run(){

    pthread_join(this->thread,NULL);

    return 0;
}*/
