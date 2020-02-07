#ifndef COMMON_H
#define COMMON_H

#include <GL/glut.h>
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define M_PI 3.14159265358979323846

typedef struct pos2 {
    float x;
    float y;
} pos2;

typedef struct pos3 pos3;
struct pos3 {
    float x;
    float y;
    float z;
};

typedef struct Vertex {
    pos3 pos;
    pos3 color;
    pos2 uv;
} Vertex;

typedef struct glVert {
} glVert;

typedef enum Camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} Camera_movement;



#endif