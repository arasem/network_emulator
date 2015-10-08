
#include "conf.h"
#include "iostream"
#include  "pthread.h"
#include "stdlib.h"
#include "elements.h"
#include "sim.h"
#include <sys/resource.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
static void event_cb(port *port_p ){
    //int *value = (int*)(data);


    std::cout<<"thread1s input number :" << port_p->input_number << "\n"<< std::endl;
    std::cout<<"thread1s problem :" << port_p->input_p[0]->problem << "\n"<< std::endl;



}

static void event_cb2(port *port_p ){
    //int *value = (int*)(data);

    std::cout<<"thread2s input number :" << port_p->input_number << "\n"<< std::endl;
    std::cout<<"thread2s problem :" << port_p->input_p[0]->problem << "\n"<< std::endl;


}

static void event_cb3(port *port_p ){
    //int *value = (int*)(data);

    std::cout<<"thread3s input number :" << port_p->input_number << "\n"<< std::endl;
    std::cout<<"thread3s problem :" << port_p->input_p[0]->problem << "\n"<< std::endl;


}

int main(int argc, char *argv[]){
  /*  int stack_size,opt;
    void *res;
 const rlim_t kStackSize = 256L * 1024L * 1024L;   // min stack size = 64 Mb
    struct rlimit rl;
rl.rlim_cur = kStackSize;
setrlimit(RLIMIT_STACK, &rl);
    stack_size = -1;
    while ((opt = getopt(argc, argv, "s:")) != -1) {
       switch (opt) {
       case 's':
           stack_size = strtoul(optarg, NULL, 0);
           break;

       default:
           fprintf(stderr, "Usage: %s [-s stack-size] arg...\n",
                   argv[0]);
           exit(EXIT_FAILURE);
       }
    }
*/
    int value = DUMMY;

    node **node_array;
    port *port_node0 = new port;
    port *port_node1 = new port;
    connection **input_array_node0;
    connection **input_array_node1;
    connection **output_array_node0;
    connection **output_array_node1;

    node_array = new node *[3];



    input_array_node0 = new connection *[1];
    input_array_node1 = new connection *[1];
    output_array_node0 = new connection *[1];
    output_array_node1 = new connection *[1];

    input_array_node0[0] =  new connection;
    input_array_node0[0]->problem = 1;

    input_array_node1[0] =  new connection;
    input_array_node1[0]->problem = 0;

    port_node0->input_number = 1;
    port_node0->input_p = input_array_node0;
    port_node0->output_number = 1;
    port_node0->output_p = input_array_node1;

    port_node1->input_number = 1;
    port_node1->input_p = input_array_node1;
    port_node1->output_number = 1;
    port_node1->output_p = input_array_node0;

    node_array[0] = new node;
    node_array[0]->cb = event_cb;
    node_array[0]->problem = 1;
    node_array[0]->port_p = port_node0;
    node_array[0]->ms_interaction_time = 0;
    node_array[1] = new node;
    node_array[1]->cb = event_cb2;
    node_array[1]->problem = 1;
    node_array[1]->port_p = port_node1;
    node_array[1]->ms_interaction_time = 20;
    node_array[2] = new node;
    node_array[2]->cb = event_cb3;
    node_array[2]->problem = 1;
    node_array[2]->port_p = port_node1;
    node_array[2]->ms_interaction_time = 40;



    network *network1 = new network;
    std::cout << "Hello \n" << std::endl;


    network1->node_number = 3;
    network1->node_p = node_array;
    sim sim1(45,5);
   // sim1.create(network1);
    sim1.run(network1);

    while(1);

return 0;

}

