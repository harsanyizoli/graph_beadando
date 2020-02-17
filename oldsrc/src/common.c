#include "common.h"

pos3 normalize_pos3(pos3 v){
    pos3 res;
    float lenght = v.x*v.x + v.y*v.y + v.z*v.z;
    res.x = v.x/sqrtf(lenght);
    res.y = v.y/sqrtf(lenght);
    res.z = v.z/sqrtf(lenght);
    return res;
}

pos3 cross_pos3(pos3 a, pos3 b){
    pos3 res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}