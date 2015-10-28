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
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

int global_sim = 1;
sem_t sem;
pthread_mutex_t lock;
event_list **event_array;
int ms_resolution_global = 0;
int current_sim_time = 0;
int current_time = 0;
bool sim_not_finished = 1;
bool regular_thread_finished = 0;
bool periodic_thread_finished = 0;
int regular_engine_event_counter = 0;
bool *global_prob;

sim::sim(int ms_time, int ms_resolution){
    int dummy;

    ms_sim_time = ms_time;
    ms_sim_resolution = ms_resolution;
    ms_resolution_global = ms_resolution;

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


void *regular_engine(void *p_engine_struct){
    int event_;
    engine_struct_t *params = (engine_struct_t *)p_engine_struct;

    while(sim_not_finished){
         if(regular_thread_finished == 0){
            if(params->prob[regular_engine_event_counter]){
                std::cout<<"Problem occured at Simulation time" << current_time << "ms \n"<< std::endl;
            }else{
                if(event_array[regular_engine_event_counter]->empty_step == false){

                    if(event_array[regular_engine_event_counter]->event_number == 1){
                        params->network_p->node_p[event_array[regular_engine_event_counter]->event_array[0]]->behaviour(params->network_p->node_p[event_array[regular_engine_event_counter]->event_array[0]]->port_p);
                    }else{
                        for(event_ = 0; event_ < event_array[regular_engine_event_counter]->event_number;event_++){
                            pthread_create(&(params->network_p->node_p[event_array[regular_engine_event_counter]->event_array[event_]]->thread),NULL, thread_func, (void *) (params->network_p->node_p[event_array[regular_engine_event_counter]->event_array[event_]]));
                        }
                        for(event_ = 0; event_ < event_array[regular_engine_event_counter]->event_number;event_++){
                            pthread_join((params->network_p->node_p[event_array[regular_engine_event_counter]->event_array[event_]]->thread),NULL);
                        }
                    }

                }
            }
            regular_thread_finished = 1;
        }
    }

    pthread_exit(0);
}

void *periodic_engine(void *params){
    network *p_network = new network;
    p_network = (network *)params;
    int node_counter = 0;
    int problem_number;

    while(sim_not_finished){
    if(periodic_thread_finished == 0){
        for(node_counter = 0; node_counter < p_network->node_number; node_counter++){
            if(p_network->node_p[node_counter]->continious){
                if(p_network->node_p[node_counter]->ms_interaction_time < current_time){
                        if(global_prob[((p_network->node_p[node_counter]->ms_interaction_time )/ ms_resolution_global) -1])
                        {
                            std::cout<<"Problem occured at Simulation time" << current_time << "ms \n"<< std::endl;
                        }else{
                            p_network->node_p[node_counter]->behaviour(p_network->node_p[node_counter]->port_p);
                        }
                }
            }
        }
        periodic_thread_finished = 1;
    }
    }



    pthread_exit(0);

}
/*
bool sim::create(node *node_p){

    pthread_create(&(this->thread),NULL, thread_func, (void *) node_p);

    return 0;

};
*/

bool nextBool(double probability)
{

    srand(time(0));
    return rand() <  probability * ((double)RAND_MAX + 1.0);
}

bool sim::create(network *network_p){
    int scale;
    const int nrolls = 10000;  // number of experiments
    int nintervals; // number of intervals
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    float lambda;
    float alfa;
    bool dummy[this->event_number];
    double dummy2[this->event_number];
    global_prob = (bool *) malloc(this->event_number + 1);

    scale = this->event_number / 20;

    switch(this->distribution_t){
        case EXPONENTIAL_DIST:
            alfa = 1.0;
            lambda = 0.2;
            nintervals= this->event_number;
            //nrolls = 10000;
        break;
        case WEIBULL_DIST:
            alfa= 1;//shape parameter
            lambda = 0.2;//1/lambda = failure rate
            nintervals= this->event_number;
            //nrolls = 1000;
        break;
        default:
        std::cout << "you didnt select distribution option" << std::endl;
        while(1);
        break;
    }

    std::weibull_distribution<double> distribution(alfa,lambda);

    int* p= new int[this->event_number];
    double *prob = new double[this->event_number];
    bool *real_prob = new bool[this->event_number + 1];

    for (int i=0; i<nrolls; ++i) {
    double number = distribution(generator);
    if (number<1.0)  ++p[int(nintervals*number)];
    }
    for (int i=0; i<this->event_number + 1; ++i) {
        prob[i]= double(p[i]*scale)/double(nrolls);
        dummy2[i] = prob[i];
        real_prob[i] = nextBool(prob[i]);
        dummy[i] = real_prob[i] ;
    }
    global_prob = real_prob;
    this->prob = real_prob;

    return 0;
}

bool sim::run(network *network_p){
    pthread_t regular_engine_thread,periodic_engine_thread;
    engine_struct_t regular_engine_struct;
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

    while(this->current_sim_time < (this->ms_sim_time + 1)){
        event_array[event_counter] = new event_list;
        event_array[event_counter]->empty_step = true;
        for(node_counter = 0; node_counter < network_p->node_number;node_counter++){
            if(network_p->node_p[node_counter]->ms_interaction_time == current_sim_time){
                event_ ++;
                event_array[event_counter]->event_number = event_;
                event_array[event_counter]->event_array[event_ - 1]= node_counter;
                event_array[event_counter]->empty_step = false;

            }
        }
        event_ = 0;
        event_counter++;
        current_sim_time = current_sim_time + this->ms_sim_resolution;

    }



    regular_engine_struct.event_number = this->event_number;
    regular_engine_struct.prob = this->prob;
    regular_engine_struct.network_p = network_p;

//
    pthread_create(&regular_engine_thread,NULL,regular_engine,(void *)&regular_engine_struct);

    pthread_create(&periodic_engine_thread,NULL,periodic_engine,(void *)network_p);
    //pthread_join(periodic_engine_thread,NULL);
   while(current_time < this->ms_sim_time){
        if(periodic_thread_finished == 1 && regular_thread_finished == 1){
        current_time = current_time + this->ms_sim_resolution;
        std::cout<<"Simulation time" << current_time << "ms \n"<< std::endl;
        periodic_thread_finished = 0;
        regular_thread_finished = 0;
        regular_engine_event_counter++;
        }
    }
    sim_not_finished = 0;
    pthread_join(periodic_engine_thread,NULL);
    pthread_join(regular_engine_thread,NULL);
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
