#ifndef UTIL_H
#define UTIL_H
#include "common.h"

void print_time(struct timeval start_time, struct timeval t);
float get_delta_since_start(struct timespec start);
#endif