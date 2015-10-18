#ifndef SIM_H
#define SIM_H

#include "elements.h"
#include "pthread.h"


typedef enum{
    EXPONENTIAL_DIST,
    WEIBULL_DIST
}distribution_option_t;


class sim{
    private:
        int current_sim_time = 0;
        int event_number;
        bool *prob;
    public:
        int ms_sim_time;
        int ms_sim_resolution;
        distribution_option_t distribution_t;
        //bool create(node *node_p);
        bool create(network *network_p);
        bool run(network *network_p);
        sim(int , int  );
};

class event_list{
    public:
    int ms_event_time;
    int event_array[50];
    int event_number;
    bool empty_step;
};


#endif
