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

//basic test
static void event_cb(port *port_p ){
    //int *value = (int*)(data);
    port_p->output_p[0]->send();
    port_p->input_p[0]->receive();

}

static void event_cb2(port *port_p ){
    port_p->input_p[0]->receive();
    port_p->output_p[0]->send();


}

static void event_cb3(port *port_p ){
    //int *value = (int*)(data);

    std::cout<<"thread3s input number :" << port_p->input_number << "\n"<< std::endl;
    std::cout<<"thread3s problem :" << port_p->input_p[0]->problem << "\n"<< std::endl;


}

//cluster test
static void cluster_manager(port *port_p ){

    port_p->input_p[0]->receive();
    port_p->input_p[1]->receive();
    port_p->input_p[2]->receive();
    port_p->input_p[3]->receive();

    port_p->output_p[0]->send();
    port_p->output_p[1]->send();
    port_p->output_p[2]->send();
    port_p->output_p[3]->send();

}

static void node0(port *port_p ){


    port_p->output_p[0]->send();
    port_p->input_p[0]->receive();


}
static void node1(port *port_p ){

    port_p->output_p[0]->send();
    port_p->input_p[0]->receive();

}
static void node2(port *port_p ){

    port_p->output_p[0]->send();
    port_p->input_p[0]->receive();

}
static void node3(port *port_p ){

    port_p->output_p[0]->send();
    port_p->input_p[0]->receive();

}




network* test_cluster(void){

  node **node_array;
    port *port_node0 = new port;
    port *port_node1 = new port;
    port *port_node2 = new port;
    port *port_node3 = new port;
    port *port_node4 = new port;
    connection **link0;
    connection **link1;
    connection **link2;
    connection **link3;
    connection **link4;
    connection **link5;
    connection **link6;
    connection **link7;

    node_array = new node *[4];
    link0 = new connection *[1];
    link1 = new connection *[1];
    link2 = new connection *[1];
    link3 = new connection *[1];
    link4 = new connection *[1];
    link5 = new connection *[1];
    link6 = new connection *[1];
    link7 = new connection *[4];
    link0[0] = new connection(5);
    link0[0]->problem = 0;
    link1[0] = new connection(5);
    link1[0]->problem = 0;
    link2[0] = new connection(5);
    link2[0]->problem = 0;
    link3[0] = new connection(5);
    link3[0]->problem = 0;
    link4[0] = new connection(5);
    link4[0]->problem = 0;
    link5[0] = new connection(5);
    link5[0]->problem = 0;
    link6[0] = new connection(5);
    link6[0]->problem = 0;
    link7[0] = new connection(5);
    link7[0]->problem = 0;


    port_node0->input_number = 1;
    port_node0->input_p = link0;
    port_node0->output_number = 1;
    port_node0->output_p = link1;

    port_node1->input_number = 1;
    port_node1->input_p = link2;
    port_node1->output_number = 1;
    port_node1->output_p = link3;


    port_node2->input_number = 1;
    port_node2->input_p = link4;
    port_node2->output_number = 1;
    port_node2->output_p = link5;

    port_node3->input_number = 1;
    port_node3->input_p = link6;
    port_node3->output_number = 1;
    port_node3->output_p = link7;


    port_node4->input_number = 4;
    port_node4->input_p = new connection *[5];
    port_node4->input_p = link1;
    port_node4->input_p[1] = link3[0];
    port_node4->input_p[2] = link5[0];
    port_node4->input_p[3] = link7[0];
    port_node4->output_number = 4;
    port_node4->output_p = new connection *[5];
    port_node4->output_p = link0;
    port_node4->output_p[1] = link2[0];
    port_node4->output_p[2] = link4[0];
    port_node4->output_p[3] = link6[0];


    node_array[0] = new node;
    node_array[0]->cb = node0;
    node_array[0]->problem = 0;
    node_array[0]->port_p = port_node0;
    node_array[0]->ms_interaction_time = 0;
    node_array[0]->continious = 1;

    node_array[1] = new node;
    node_array[1]->cb = node1;
    node_array[1]->problem = 0;
    node_array[1]->port_p = port_node1;
    node_array[1]->ms_interaction_time = 0;
    node_array[1]->continious = 1;

    node_array[2] = new node;
    node_array[2]->cb = node2;
    node_array[2]->problem = 0;
    node_array[2]->port_p = port_node2;
    node_array[2]->ms_interaction_time = 0;
    node_array[2]->continious = 1;

    node_array[3] = new node;
    node_array[3]->cb = node3;
    node_array[3]->problem = 0;
    node_array[3]->port_p = port_node3;
    node_array[3]->ms_interaction_time = 0;
    node_array[3]->continious = 1;

    node_array[4] = new node;
    node_array[4]->cb = cluster_manager;
    node_array[4]->problem = 0;
    node_array[4]->port_p = port_node4;
    node_array[4]->ms_interaction_time = 0;
    node_array[4]->continious = 1;


    network *network1 = new network;
    network1->node_number = 5;
    network1->node_p = node_array;

    return network1;


}

network* test_network(void){


    node **node_array;
    port *port_node0 = new port;
    port *port_node1 = new port;
    connection **link0;
    connection **link1;

    node_array = new node *[2];
    link0 = new connection *[1];
    link1 = new connection *[1];
    link0[0] = new connection(5);
    link0[0]->problem = 0;
    link1[0] = new connection(5);
    link1[0]->problem = 0;


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

    network *network1 = new network;
    network1->node_number = 2;
    network1->node_p = node_array;

    return network1;

}
