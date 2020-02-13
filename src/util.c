#include "util.h"

void print_time(struct timeval start_time, struct timeval t){

}

float get_delta_since_start(struct timespec start){
    struct timespec curr;
    clock_gettime(CLOCK_REALTIME, &curr);
    float sec_since_start = (float)(curr.tv_sec - start.tv_sec) + (float)(curr.tv_nsec - start.tv_nsec) / 1000000000.f;
    return sec_since_start;
}