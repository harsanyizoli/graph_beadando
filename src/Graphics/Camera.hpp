#ifndef CAMERA_H
#define CAMERA_H

#include "../common.hpp"

enum Player_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH =  0.0f;
const float BASE_SPEED =  10.0f;
const float SENSITIVITY =  0.1f;
const float ZOOM =  45.0f;


class Camera
{
public:

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Player options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, 1.0f)), MovementSpeed(BASE_SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat3 GetViewMatrix() const 
    {
        //return glm::lookAt(Position, Position + Front, Up);
        return glm::mat3(Position,glm::vec3(Position.x + Front.x, Position.y + Front.y, Position.z + Front.z), Up);
    }

    void ProcessKeyboard(Player_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            Position += Front * glm::vec3(velocity, 0.0f, velocity);
            //std::cout << velocity << " ";
            //std::cout << Pitch << " " << Yaw << " " << MovementSpeed << std::endl;
        }
        if (direction == BACKWARD)
            Position -= Front * glm::vec3(velocity, 0.0f, velocity);
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
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
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            // Also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up    = glm::normalize(glm::cross(Right, Front));
        }
};

#endif