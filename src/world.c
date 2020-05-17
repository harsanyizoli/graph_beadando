#include "world.h"

void init_world(struct World *w){
    w->ball = (struct Ball*)malloc(sizeof(struct Ball));
    w->ball->add.x = 0.0f;
    w->ball->add.y = 0.0f;
    w->ball->add.z = 0.0f;

    w->ball->ball_pos.x = 0.0f;
    w->ball->ball_pos.y = 0.0f;
    w->ball->ball_pos.z = 4.0f;

    w->ball->nohit = 0;
    w->ball->ball_tex = load_texture("assets/ehe.png", w->ball->ball_img);
    //
    w->car = (struct Car*)malloc(sizeof(struct Car));
    w->car->m_car = (struct Model*)malloc(sizeof(struct Model));

    w->car->car_pos.x = 0.0f;
    w->car->car_pos.y = 0.0f;
    w->car->car_pos.z = 0.0f;
    load_model("assets/red.obj", w->car->m_car);
    w->car->car_tex = load_texture("assets/red.png", w->car->car_img);

    w->light = (struct Light*)malloc(sizeof(struct Light));
    w->light->pos.x = 0.0f;
    w->light->pos.y = 20.0f;
    w->light->pos.z = 0.0f;
    w->light->ambient = 0.0f;

    w->floor = (struct Floor*)malloc(sizeof(struct Floor));
    w->floor->floor_tex = load_texture("assets/grass14.png", w->floor->floor_img);
    w->floor->size = 20;
}

void init_help(struct Help *help){
    help->help_tex = load_texture("assets/help.png", help->help_img);
    help->on = 0;
}