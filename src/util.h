#ifndef UTIL_H
#define UTIL_H
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include "SOIL/SOIL.h"
typedef struct Model Model;
struct vec3f {
    union {
        float x;
        float r;
    };
    union {
        float y;
        float g;
    };
    union {
        float z;
        float b;
    };
};
typedef struct vec3f vec3f;

typedef enum Camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} Camera_movement;

typedef GLubyte Pixel[3];

float get_delta_since_start(struct timespec start);
vec3f normalize_vec3f(vec3f v);
vec3f cross_vec3f(vec3f a, vec3f b);
vec3f add_vec3f(vec3f a, vec3f b);
vec3f sub_vec3f(vec3f a, vec3f b);
vec3f mult_vec3f(vec3f a, float b);
GLuint load_texture(char* filename, Pixel* image);

#endif