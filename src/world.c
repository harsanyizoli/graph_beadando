#include "model.h"
#include "common.h"
#include "world.h"

void init_world(struct World* w){
    w->size = 64;
    w->num_of_objs = 0;
    w->objects = (Object*)malloc(sizeof(Object) * 64);
}

void add_object(struct World* w, const char* filename){
    w->objects[w->num_of_objs].m = (struct Model*)malloc(sizeof(struct Model));
    load_model(filename, w->objects[0].m);
    print_model_info(w->objects[0].m);
    w->objects[0].position.x = 0.0f;
    w->objects[0].position.y = 0.0f;
    w->objects[0].position.z = 0.0f;
    w->objects[0].rotatex = 0.0f;
    w->objects[0].rotatey = 0.0f;
    w->objects[0].rotatez = 0.0f;
    w->objects[0].scale = 0.5f;
}