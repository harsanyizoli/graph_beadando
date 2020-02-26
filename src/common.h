#ifndef COMMON_H
#define COMMON_H

#include <GL/glut.h>
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <memory.h>

#define M_PI 3.14159265358979323846

typedef struct Model Model;

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

typedef enum Camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} Camera_movement;

pos3 normalize_pos3(pos3 v);
pos3 cross_pos3(pos3 a, pos3 b);
typedef GLubyte Pixel[3];

typedef struct Object {
    Model* m;
    Pixel* image;
    GLuint texture;
    pos3 position;
    float rotatex, rotatey, rotatez;
    float scale;
    char name[64];
} Object;

GLuint load_texture(char* filename, Pixel* image);

#endif