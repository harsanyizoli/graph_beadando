#include "camera.h"

    /*glm::mat4 GetViewMatrix() const 
    {
        return glm::lookAt(Position, Position + Front, Up);
    }*/
void init_cam(struct Camera* c){
    c->Position.x = 0.0f;
    c->Position.y = 0.25f;
    c->Position.z = -3.0f;
    c->Front.x = 0.0f;
    c->Front.y = 0.0f;
    c->Front.z = 1.0f;
    c->Up.x = 0.0f;
    c->Up.y = 1.0f;
    c->Up.z = 0.0f;
    c->Right.x = -1.0f;
    c->Right.y = 0.0f;
    c->Right.z = 0.0f;
    c->MovementSpeed = 3.0f;
    c->MouseSensitivity = 0.05f;
    c->Yaw = 90.0f;
    c->Zoom = 1.0f;
    c->Pitch = 0.0f;
}
void process_key(struct Camera* c, Camera_movement direction, float delta)
{
    float velocity = c->MovementSpeed * delta;
    if (direction == FORWARD){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        c->Position.x += c->Front.x * velocity;
        //c->Position.y += c->Front.y * velocity;
        c->Position.z += c->Front.z * velocity;
    }
    if (direction == BACKWARD){
        c->Position.x -= c->Front.x * velocity;
        //c->Position.y -= c->Front.y * velocity;
        c->Position.z -= c->Front.z * velocity;
        }
    if (direction == LEFT){
        c->Position.x -= c->Right.x * velocity;
        //c->Position.y -= c->Right.y * velocity;
        c->Position.z -= c->Right.z * velocity;
    }
    if (direction == RIGHT){
        c->Position.x += c->Right.x * velocity;
        //c->Position.y += c->Right.y * velocity;
        c->Position.z += c->Right.z * velocity;
    }
}
float degree_to_radian(float degree){
    return degree * M_PI / 180.f;
}

void set_view_point(const struct Camera* c){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    //printf("lookat position x: %f, y: %f, z: %f\n", c->Position.x, c->Position.y, c->Position.z);
    //printf("looakt front x: %f, y: %f, z: %f\n", c->Front.x, c->Front.y, c->Front.z);
	gluLookAt(
        c->Position.x, c->Position.y, c->Position.z, // eye
        c->Position.x + c->Front.x, c->Position.y + c->Front.y, c->Position.z + c->Front.z, // look at
        0.0, 1.0, 0.0  // up
    );
    glutPostRedisplay();
}



    void process_mouse_movement(struct Camera* c, float xoffset, float yoffset)
    {
        pos3 f;
        //printf("-------------------\nxoffset: %f, yoffset: %f\n", xoffset, yoffset);

        xoffset *= c->MouseSensitivity;
        yoffset *= c->MouseSensitivity;

        c->Yaw   += xoffset;
        c->Pitch += yoffset;
        //printf("YAW: %f, PITCH: %f\n", c->Yaw, c->Pitch);
        if (1)
        {
            if (c->Pitch > 89.9f)
                c->Pitch = 89.9f;
            if (c->Pitch < -89.9f)
                c->Pitch = -89.9f;
        }
        f.x = cos(degree_to_radian(c->Yaw)) * cos(degree_to_radian(c->Pitch));
        f.y = sin(degree_to_radian(c->Pitch));
        f.z = sin(degree_to_radian(c->Yaw)) * cos(degree_to_radian(c->Pitch));

        c->Front = normalize_pos3(f);
        c->Right = normalize_pos3(cross_pos3(c->Front, c->Up));
        // Make sure that when pitch is out of bounds, screen doesn't get flipped

        // Update Front, Right and Up Vectors using the updated Euler angles
        //std::cout << Front.x << " " << Front.y << " " << Front.z << std::endl;
    }



/*

    ~Camera();
private:
    void updateCameraVectors()
        {
            
            // Calculate the new Front vector
            pos3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            // Also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up    = glm::normalize(glm::cross(Right, Front));
            
        }
        */