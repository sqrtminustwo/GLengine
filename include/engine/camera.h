#ifndef CAMERA_H
#define CAMERA_H

#include <glm/ext/matrix_transform.hpp>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 1.5f;
constexpr float SENSITIVITY = 0.03f;
constexpr float ZOOM = 45.0f;

class Camera {
  public:
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH
    );
    Camera(
        float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch
    );

    glm::mat4 getViewMatrix() const { return glm::lookAt(Position, Position + Front, Up); }
    glm::vec3 getPosition() const { return Position; }

    void change_fps() { fps = !fps; }

    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    bool processKeyboard(const Camera_Movement direction, const float deltaTime);
    void ProcessMouseScroll(const float yoffset);

  private:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    bool fps = false;

    void updateCameraVectors();
};
#endif
