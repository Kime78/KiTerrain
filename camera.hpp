#pragma once
#include <glm.hpp>
#include <GLFW/glfw3.h>

class Camera 
{
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::mat4 view;

public:
    Camera();
    void handle_input(GLFWwindow *window);
    void upload_uniform();
};