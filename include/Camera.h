#pragma once
#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "shaderClass.h"

class Camera {
    public:
        glm::vec3 Position, resetPosition;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

        int width, height;

        float speed = 0.1f; //speed of camera
        float sensitivity = 100.0f; // sensitivity when moving around

        Camera(int width, int hiehgt, glm::vec3 position); // simple constructor

        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform); // send create and view projection matrixes to the shader
        void Inputs(GLFWwindow* window); //handle inputs
};

#endif