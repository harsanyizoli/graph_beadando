#ifndef world_h
#define world_h
#include "common.h"
#include "util.h"

struct Car {
    Model* m_car;
    Pixel* car_img;
    GLuint car_tex;
    vec3f car_pos;
};
struct Ball {
    Pixel* ball_img;
    GLuint ball_tex;
    vec3f ball_pos;
    vec3f add;
    uint8_t nohit;
};

struct Light {
    vec3f pos;
    float ambient;
};

struct World {
    struct Car *car;
    struct Ball *ball;
    struct Light *light;
};

void init_world(struct World *w);
#endif // !world_h