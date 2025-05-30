#include <iostream>
#include <stdexcept> // for std::runtime_error
#include <filesystem>

// External libs
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Engine components
#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Camera.h"

const unsigned int initialWidth = 600;
const unsigned int initialHeight = 600;

Camera* mainCamera = nullptr;

// Framebuffer resize callback to update viewport and camera size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	if (width == 0 || height == 0) return; // avoid issues on minimized window
	glViewport(0, 0, width, height);
	if (mainCamera) {
		mainCamera->UpdateSize(width, height);
	}
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		glfwSetWindowTitle(window, "I HAVE NO IDEA WHAT I'M DOING!!!!!!");
}

const unsigned int width = 600;
const unsigned int height = 600;

GLfloat vertices[] = {
	-0.5f,  0.0f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	-0.5f,  0.0f, -0.5f,   1.0f, 1.0f, 0.0f,   5.0f, 0.0f,
	 0.5f,  0.0f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	 0.5f,  0.0f,  0.5f,   1.0f, 1.0f, 1.0f,   5.0f, 0.0f,
	 0.0f,  0.8f,  0.0f,   1.0f, 1.0f, 1.0f,   2.5f, 2.5f,
};

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4,
};

int main() {
	try {
		// --- GLFW Init ---
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(width, height, "PrismGL", nullptr, nullptr);
		if (!window)
			throw std::runtime_error("Failed to create GLFW window");

		glfwMakeContextCurrent(window);

		if (!gladLoadGL())
			throw std::runtime_error("Failed to initialize GLAD");

		glViewport(0, 0, initialWidth, initialHeight);
		glEnable(GL_DEPTH_TEST);

		// --- Shader, VAO/VBO/EBO setup ---
		Shader shaderProgram;

		VAO VAO1;
		VAO1.Bind();

		VBO VBO1(vertices, sizeof(vertices));
		EBO EBO1(indices, sizeof(indices));

		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		if (!std::filesystem::exists("../res/aigis.png")) {
    	throw std::runtime_error("Missing texture: ../res/aigis.png");
		}
		Texture toaster("../res/aigis.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

		toaster.texUnit(shaderProgram, "tex0", 0);

		Camera camera(initialWidth, initialHeight, glm::vec3(0.0f, 0.0f, 2.0f));
		mainCamera = &camera;
		while (!glfwWindowShouldClose(window)) {
			processInput(window);

			glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			shaderProgram.Activate();
			camera.Inputs(window);
			camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

			toaster.Bind();
			VAO1.Bind();
			glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		VAO1.Delete();
		VBO1.Delete();
		EBO1.Delete();
		toaster.Delete();
		shaderProgram.Delete();
		glfwDestroyWindow(window);
		glfwTerminate();

		return 0;

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	} catch (int errCode) {
		std::cerr << "Caught integer exception: " << errCode << std::endl;
	} catch (...) {
		std::cerr << "Unknown error occurred." << std::endl;
	}
	return 1;
}
