#if !defined(WORLD_H)
#define WORLD_H

struct World
{
    int size;
    Object* objects;
    int num_of_objs;
};

void init_world(struct World* w);
int add_object(struct World* w, const char* filename);
void add_texture_for_obj(struct World* w, int object_id, const char* filename);
void move_object(struct World* w, int object_id, float x, float y, float z);
void scale_object(struct World* w, int object_id, float x);
int add_obj_with_text(struct World* w, const char* objname, const char* texname);
#endif // WORLD_H
