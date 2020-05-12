#ifndef UTIL_H
#define UTIL_H
#include "common.h"

void print_time(struct timeval start_time, struct timeval t);
float get_delta_since_start(struct timespec start);
vec3f normalize_vec3f(vec3f v);
vec3f cross_vec3f(vec3f a, vec3f b);
vec3f add_vec3f(vec3f a, vec3f b);
vec3f sub_vec3f(vec3f a, vec3f b);
vec3f mult_vec3f(vec3f a, float b);
GLuint load_texture(char* filename, Pixel* image);

#endif