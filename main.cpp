
#include "conf.h"
#include "iostream"
#include  "pthread.h"
#include "stdlib.h"
#include "elements.h"
#include "sim.h"
#include "network_test.h"
#include <sys/resource.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <random>

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

    std::cout << "Hello \n" << std::endl;
    sim_statistical_t results;

    network *network1 = new network;
    network1 = test_network();
    sim sim1(600,5);
    sim1.distribution_t = WEIBULL_DIST;
    sim1.create(network1);
    sim1.run(network1);
    sim1.statistics(&results,network1);
    std::cout <<"packet sent counter: "<< results.sent_packet_number << "\n" << std::endl;
    std::cout <<"packet received counter: "<< results.received_packet_number << "\n" << std::endl;
    std::cout <<"success ratio  : "<< results.success_ratio << "\n" << std::endl;
    std::cout <<"throughput  : "<< results.throughput << "\n" << std::endl;
/*
    const int nrolls=10000;  // number of experiments
    const int nstars=100;    // maximum number of stars to distribute
    const float lambda = 1/3.5;
    std::default_random_engine generator;
    //std::weibull_distribution<double> distribution(1.0,1.0);
     std::exponential_distribution<double> distribution(3.5);
    int p[200]={};
    for (int i=0; i<nrolls; ++i) {
        double number = distribution(generator);
        if (number<1.0) ++p[int(200*number)];
    }

    std::cout << "exponential_distribution (3.5):" << std::endl;
    std::cout << std::fixed; std::cout.precision(5);
    for (int i=0; i<200; ++i) {
        std::cout << i << "-" << (i+1) << ": ";
            std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
       // std::cout << float(p[i])/nrolls << std::endl;
}
*/
    while(1);

return 0;

}

