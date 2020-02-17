#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

struct Camera
{
    pos3 Position;
    pos3 Front;
    pos3 Right;
    pos3 Up;
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