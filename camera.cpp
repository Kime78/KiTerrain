#include "glad.h"
#include "camera.hpp"

#include "shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera() {
    cameraPos   = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
    view        = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::handle_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += 0.01f * cameraFront;
        // cameraPos -= cameraUp * 0.0001f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= 0.01f * cameraFront;
        // cameraPos += cameraUp * 0.0001f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPos += cameraUp * 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraPos += cameraUp * -0.01f;
    }
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glfwGetCursorPos(window, &xpos, &ypos);
    // camera
    // xpos = sf::Mouse::getPosition().x;
    // ypos = sf::Mouse::getPosition().y;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX         = xpos;
    lastY         = ypos;

    float sensitivity = 0.1;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::upload_uniform() {
    Shader sh;
    GLint viewLocation =
        glGetUniformLocation(sh.shaderProgram, "view");   // get the shader mat4
    glUniformMatrix4fv(
        viewLocation, 1, GL_FALSE,
        glm::value_ptr(view));   // set the mat4 to our modified one

    GLint projLocation =
        glGetUniformLocation(sh.shaderProgram, "proj");   // get the shader mat4
    glm::mat4 projection =
        glm::perspective(glm::radians(90.0f), 1200.0f / 700.0f, 0.1f, 1000.0f);
    glUniformMatrix4fv(
        projLocation, 1, GL_FALSE,
        glm::value_ptr(projection));   // set the mat4 to our modified one
}