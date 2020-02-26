#include "model.h"
#include "common.h"
#include "world.h"

void init_world(struct World* w){
    w->objects = (Object*)malloc(sizeof(Object) * 64);
}

int add_object(struct World* w, const char* filename){
    char file[32] = "assets/";
    strcat(file, filename);
    w->objects[w->num_of_objs].m = (struct Model*)malloc(sizeof(struct Model));
    load_model(file, w->objects[w->num_of_objs].m);
    print_model_info(w->objects[w->num_of_objs].m);
    w->objects[w->num_of_objs].position.x = 0.0f;
    w->objects[w->num_of_objs].position.y = 0.0f;
    w->objects[w->num_of_objs].position.z = 0.0f;
    w->objects[w->num_of_objs].rotatex = 0.0f;
    w->objects[w->num_of_objs].rotatey = 0.0f;
    w->objects[w->num_of_objs].rotatez = 0.0f;
    w->objects[w->num_of_objs].scale = 1.0f;
    strcpy(w->objects[w->num_of_objs].name, file);
    w->num_of_objs += 1;
    return w->num_of_objs - 1;
}

void move_object(struct World* w, int object_id, float x, float y, float z){
    w->objects[object_id].position.x += x;
    w->objects[object_id].position.y += y;
    w->objects[object_id].position.z += z;
}

void scale_object(struct World* w, int object_id, float x){
    w->objects[object_id].scale += x;
}
void add_texture_for_obj(struct World* w, int object_id, const char* filename){
    char file[32] = "assets/";
    strcat(file, filename);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    w->objects[object_id].texture = load_texture(file, w->objects[object_id].image);
    printf("loading texture %s\n", file);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	glEnable(GL_TEXTURE_2D);
}

int add_obj_with_text(struct World* w, const char* objname, const char* texname){
    int i = add_object(w, objname);
    printf("added id %d\n", i);
    add_texture_for_obj(w, i, texname);
    printf("loaded texture for %d\n", i);
    return i;
}