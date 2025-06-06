#include "Camera.h"
#include<iostream>

Camera::Camera(int width, int height, glm::vec3 position) {
    Camera::width = width;
    Camera::height = height;
    Position = position;
    glm::vec3 resetPosition = Position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view)); //export matrix to vertex shader
}

void Camera::Inputs(GLFWwindow* window) {
    //Move
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) Position += speed * Orientation;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) Position += speed * -Orientation;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) Position += speed * glm::normalize(glm::cross(Orientation, Up));
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) Position += speed * Up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) Position += speed * -Up;
    // if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS) Position = resetPosition;
    // Speed
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed = 0.04f;
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed = 0.001f;
    // Look Around
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (height / 2)) / height;

        //prevent barrel rolls!
        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

        if (!(glm::angle(newOrientation, Up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))) {
            Orientation = newOrientation;
        }

        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Camera::UpdateSize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}