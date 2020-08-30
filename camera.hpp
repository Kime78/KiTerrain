#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::mat4 view;

    float yaw = 0;
    float pitch;
    float lastX = 0;
    float lastY = 0;
    double xpos = 0;
    double ypos = 0;

public:
    Camera();
    void handle_input(GLFWwindow* window);
    void upload_uniform();
};