#if !defined(WOLD_H)
#define WOLD_H

#include "common.h"

typedef struct World {
    Object* objects;
    unsigned int width, height;
} World;

#endif // WOLD_H
