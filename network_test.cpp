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
    std::cout<<"node1 has been started  :" << port_p->input_number << "\n"<< std::endl;
    std::cout<<" data sending....  \n"<< std::endl;
    port_p->output_p[0]->send();
  /*  received_data = port_p->input_p[0]->receive();
    if(received_data != 0){
        std::cout <<"packet has received : "<< (int) received_data << "\n" <<std::endl;
    }*/
}

static void event_cb2(port *port_p ){
    //int *value = (int*)(data);

    uint8_t data = 0;
    uint8_t received_data = 0;
   /* std::cout<<"node2 has been started  :" << port_p->input_number << "\n"<< std::endl;
    std::cout<<" data sending....  \n"<< std::endl;
    port_p->output_p[0]->send(data);*/
    received_data = port_p->input_p[0]->receive();
    if(received_data != 0){
        std::cout <<"packet has received : "<< (int) received_data << "\n" <<std::endl;
    }
     std::cout <<"packet received counter: "<< port_p->input_p[0]->packet_received << "\n" << std::endl;
     std::cout <<"packet sent counter: "<< port_p->input_p[0]->packet_sent << "\n" << std::endl;
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
    connection **link0;
    connection **link1;
    /*connection **input_array_node0;
    connection **input_array_node1;
    connection **output_array_node0;
    connection **output_array_node1;
*/
    node_array = new node *[2];
    link0 = new connection *[1];
    link1 = new connection *[1];
    link0[0] = new connection(0);
    link0[0]->problem = 0;
    link1[0] = new connection(5);
    link1[0]->problem = 0;
/*
    input_array_node0 = new connection *[1];
    input_array_node1 = new connection *[1];
    output_array_node0 = new connection *[1];
    output_array_node1 = new connection *[1];

    input_array_node0[0] =  new connection;
    input_array_node0[0]->problem = 0;

    input_array_node1[0] =  new connection;
    input_array_node1[0]->problem = 0;
*/

    port_node0->input_number = 1;
    port_node0->input_p = link0;
    port_node0->output_number = 1;
    port_node0->output_p = link1;

    port_node1->input_number = 1;
    port_node1->input_p = link1;
    port_node1->output_number = 1;
    port_node1->output_p = link0;

    node_array[0] = new node;
    node_array[0]->cb = event_cb;
    node_array[0]->problem = 0;
    node_array[0]->port_p = port_node0;
    node_array[0]->ms_interaction_time = 0;
    node_array[0]->continious = 1;
    node_array[1] = new node;
    node_array[1]->cb = event_cb2;
    node_array[1]->problem = 0;
    node_array[1]->port_p = port_node1;
    node_array[1]->ms_interaction_time = 0;
    node_array[1]->continious = 1;
    /*
    node_array[2] = new node;
    node_array[2]->cb = event_cb3;
    node_array[2]->problem = 0;
    node_array[2]->port_p = port_node1;
    node_array[2]->ms_interaction_time = 40;
    node_array[2]->continious = 0;
*/

    network *network1 = new network;
    network1->node_number = 2;
    network1->node_p = node_array;

    return network1;

}
