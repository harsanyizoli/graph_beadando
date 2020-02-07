#include "camera.h"

    /*glm::mat4 GetViewMatrix() const 
    {
        return glm::lookAt(Position, Position + Front, Up);
    }*/
void init_cam(struct Camera* c){
    c->Position.x = 0.0f;
    c->Position.y = 2.0f;
    c->Position.z = -3.0f;
    c->Front.x = 0.0f;
    c->Front.y = 0.0f;
    c->Front.z = 0.0f;
    c->MovementSpeed = 10.0f;
    c->MouseSensitivity = 0.1f;
    c->Yaw = -90.0f;
    c->Zoom = 1.0f;
    c->Pitch = 0.0f;
}
void process_key(struct Camera* c, Camera_movement direction, float deltaTime)
{
    float velocity = c->MovementSpeed * deltaTime;
    if (direction == FORWARD){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        c->Position.x += c->Front.x * velocity;
        c->Position.y += c->Front.y * velocity;
        c->Position.z += c->Front.z * velocity;
        printf("x: %f, y: %f, z: %f, vel: %f", c->Position.x, c->Position.y, c->Position.z, velocity);
    }
    if (direction == BACKWARD)
        c->Position.x -= c->Front.x * velocity;
        c->Position.y -= c->Front.y * velocity;
        c->Position.z -= c->Front.z * velocity;/*
    if (direction == LEFT)
        Position.x -= Right.x * velocity;
        Position.y -= Right.y * velocity;
        Position.z -= Right.z * velocity;
    if (direction == RIGHT)
        Position.x += Right.x * velocity;
        Position.y += Right.y * velocity;
        Position.z += Right.z * velocity;*/
}
float degree_to_radian(float degree){
    return degree * M_PI / 180.f;
}

void set_view_point(const struct Camera* c){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
        c->Position.x, c->Position.y, c->Position.z, // eye
        c->Front.x, c->Front.y, c->Front.z, // look at
        0.0, 1.0, 0.0  // up
    );
}


/*
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        if(std::abs(xoffset) >= 600 || std::abs(yoffset) >= 300){
            xoffset = 0;
            yoffset = 0;
        }
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.9f)
                Pitch = 89.9f;
            if (Pitch < -89.9f)
                Pitch = -89.9f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
        //std::cout << Front.x << " " << Front.y << " " << Front.z << std::endl;
    }

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