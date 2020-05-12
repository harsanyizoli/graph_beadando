#ifndef COMMON_H
#define COMMON_H

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <memory.h>
#include "SOIL/SOIL.h"
#define M_PI 3.14159265358979323846
typedef struct Model Model;
typedef struct vec3f vec3f;
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

typedef enum Camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} Camera_movement;

typedef GLubyte Pixel[3];

#endif