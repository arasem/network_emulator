#ifndef SIM_H
#define SIM_H

#include "elements.h"
#include "pthread.h"



class sim{
    private:
        int current_sim_time = 0;
        int event_number;
        bool *prob;
    public:
       int ms_sim_time;
        int ms_sim_resolution;
        sim(int , int  );
        //bool create(node *node_p);
        bool create(network *network_p);
        bool run(network *network_p);
};

class event_list{
    public:
    int ms_event_time;
    int event_array[50];
    int event_number;
};


#endif
