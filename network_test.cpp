#include "network_test.h"
#include <sys/resource.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <random>
#include "iostream"

static void event_cb(port *port_p ){
    //int *value = (int*)(data);
    uint8_t data[8] = { 5,1,2,3,4,5,6,7};
    uint8_t index;
    std::cout<<"node1 has been started  :" << port_p->input_number << "\n"<< std::endl;
    std::cout<<""<< " data sending....  \n"<< std::endl;
    for(index = 0; index < 8; index++){
        port_p->input_p[0]->send(data[i]);
    }
    while()


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

network* test_network(void){


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
    input_array_node0[0]->problem = 0;

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
    node_array[0]->problem = 0;
    node_array[0]->port_p = port_node0;
    node_array[0]->ms_interaction_time = 0;
    node_array[1] = new node;
    node_array[1]->cb = event_cb2;
    node_array[1]->problem = 0;
    node_array[1]->port_p = port_node1;
    node_array[1]->ms_interaction_time = 20;
    node_array[2] = new node;
    node_array[2]->cb = event_cb3;
    node_array[2]->problem = 0;
    node_array[2]->port_p = port_node1;
    node_array[2]->ms_interaction_time = 40;



    network *network1 = new network;
    network1->node_number = 3;
    network1->node_p = node_array;

    return network1;

}
