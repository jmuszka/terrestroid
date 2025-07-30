#include "camera.hpp"

glm::vec3 Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

Camera::Camera()
{
    pitch = 0.0f;
    yaw = 0.0f;
    lastX = 0.0f;
    lastY = 0.0f;
    firstMouse = true;
    
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, 1.0f);
}

Camera::Camera(glm::vec3 initialPos)
{
    Camera();
    pos = initialPos;
    front = glm::vec3(0.0f, 0.0f, 1.0f);
}

Camera::Camera(glm::vec3 initialPos, glm::vec3 initialFront)
{
    Camera();
    pos = initialPos;
    front = initialFront;
}

Camera::Camera(float initialPosX, float initialPosY, float initialPosZ)
{
    Camera();
    pos = glm::vec3(initialPosX, initialPosY, initialPosZ);
    front = glm::vec3(0.0f, 0.0f, 1.0f);
}

Camera::Camera(float initialPosX, float initialPosY, float initialPosZ, float initialFrontX, float initialFrontY, float initialFrontZ)
{
    Camera();
    pos = glm::vec3(initialPosX, initialPosY, initialPosZ);
    front = glm::vec3(initialFrontX, initialFrontY, initialFrontZ);
}

void Camera::move(int direction, float distance)
{
    switch (direction) 
    {
        case CAM_LEFT:
            pos += distance*glm::normalize(glm::cross(up, front));
            break;
        case CAM_RIGHT:
            pos -= distance*glm::normalize(glm::cross(up, front));
            break;
        case CAM_UP:
            pos += distance*up;
            break;
        case CAM_DOWN:
            pos -= distance*up;
            break;
        case CAM_BACKWARDS:
            pos -= distance*glm::normalize(glm::cross(glm::cross(up, front), up));
            break;
        case CAM_FORWARDS:
            pos += distance*glm::normalize(glm::cross(glm::cross(up, front), up));
            break;
        default:
            break;
    }
}

void Camera::look(float xpos, float ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    const float sensitivity = 0.05f;

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch -= yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    else if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}