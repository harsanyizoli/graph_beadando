#include "util.h"

void print_time(struct timeval start_time, struct timeval t){

}

float get_delta_since_start(struct timespec start){
    struct timespec curr;
    clock_gettime(CLOCK_REALTIME, &curr);
    float sec_since_start = (float)(curr.tv_sec - start.tv_sec) + (float)(curr.tv_nsec - start.tv_nsec) / 1000000000.f;
    return sec_since_start;
}


vec3f normalize_vec3f(vec3f v){
    vec3f res;
    float lenght = v.x*v.x + v.y*v.y + v.z*v.z;
    res.x = v.x/sqrtf(lenght);
    res.y = v.y/sqrtf(lenght);
    res.z = v.z/sqrtf(lenght);
    return res;
}

vec3f cross_vec3f(vec3f a, vec3f b){
    vec3f res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}

vec3f add_vec3f(vec3f a, vec3f b){
    vec3f c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return c;
}
vec3f sub_vec3f(vec3f a, vec3f b){
    vec3f c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return c;
}
vec3f mult_vec3f(vec3f a, float b){
    vec3f c;
    c.x = a.x * b;
    c.y = a.y * b;
    c.z = a.z * b;
    return c;
}
GLuint load_texture(char* filename, Pixel* image)
{
    GLuint texture_name;
    glGenTextures(1, &texture_name);

    int width;
    int height;

    image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	
    /*
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    */

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture_name;
}