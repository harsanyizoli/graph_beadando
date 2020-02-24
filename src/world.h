#if !defined(WORLD_H)
#define WORLD_H

struct World
{
    int size;
    Object* objects;
    int num_of_objs;
};

void init_world(struct World* w);
void add_object(struct World* w, const char* filename);

#endif // WORLD_H
