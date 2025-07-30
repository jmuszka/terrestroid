#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define CAM_LEFT 0
#define CAM_RIGHT 1
#define CAM_UP 2
#define CAM_DOWN 3
#define CAM_BACKWARDS 4
#define CAM_FORWARDS 5

class Camera
{

private:
    float pitch;
    float yaw;
    float lastX;
    float lastY;
    bool firstMouse;

public:
    glm::vec3 pos;
    glm::vec3 front;
    static glm::vec3 up;

    Camera();
    Camera(glm::vec3 initialPos);
    Camera(glm::vec3 initialPos, glm::vec3 initialFront);
    Camera(float initialPosX, float initialPosY, float initialPosZ);
    Camera(float initialPosX, float initialPosY, float initialPosZ, float initialFrontX, float initialFrontY, float initialFrontZ);

    void move(int direction, float distance);
    void look(float xpos, float ypos);
};