#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "util.h"

struct Camera
{
    vec3f Position;
    vec3f Front;
    vec3f Right;
    vec3f Up;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
};
void process_key(struct Camera* c, Camera_movement direction, float deltaTime);
void init_cam(struct Camera* c);
float degree_to_radian(float degree);
void set_view_point(const struct Camera* camera);
void process_mouse_movement(struct Camera* c, float xoffset, float yoffset);

#endif