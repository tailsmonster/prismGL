#include <iostream>

#define GLAD_GL_IMPLEMENTATION
#include "include/glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Camera.h"

// Get some input control in GLFW. This function returns which key is being pressed.
void processInput(GLFWwindow* window) {

	// This if statement checks if the escape key is pressed, and when it is the window is closed.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// This if statement checks if the r key is pressed, and when it is the window is renamed.
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		glfwSetWindowTitle(window, "I HAVE NO IDEA WHAT I'M DOING!!!!!!\n");
	}
}

const unsigned int width = 600;
const unsigned int height = 600;



//PRISMATIC >:D
GLfloat vertices[] = {
	//    COORDS              /      COLORS    /      TEXTURE COORDS   //

	-0.5f,  0.0f,  0.5f,       1.0f,  0.0f, 0.0f,       0.0f, 0.0f,
	-0.5f,  0.0f, -0.5f,       1.0f,  1.0f, 0.0f,       5.0f, 0.0f,
	 0.5f,  0.0f, -0.5f,       1.0f,  1.0f, 1.0f,       0.0f, 0.0f,
	 0.5f,  0.0f,  0.5f,       1.0f,  1.0f, 1.0f,       5.0f, 0.0f,
	 0.0f,  0.8f,  0.0f,       1.0f,  1.0f, 1.0f,       2.5f, 2.5f,
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
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we're using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// This means we only get the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




	// Create the GLFWwindow object of 600 x 600 pixels, called "First OpenGL Project"
	GLFWwindow* window = glfwCreateWindow(width, height, "First OpenGL Project", NULL, NULL);
	// Error check incase window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);



	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewpoint of OpenGL in the Window
	// In this case the viewpoint goes from x = 0, y = 0, to x = 600, y = 600
	glViewport(0, 0, width, height);

	// create shader object, importing shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// creates vertex array object & binds it
	VAO VAO1;
	VAO1.Bind();

	// creates vertex buffer and elements buffers objects, linking them to vertices and indices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Links our VBO to our VAO. Then unbind VAO, VBO, and EBO to prevent overwriting
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind to prevent accidentally overwriting!
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Getes ID of uniform called "scale"
	GLuint uniformID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Texture!
	Texture toaster("aigis.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	toaster.texUnit(shaderProgram, "tex0", 0);

	// Enables the Depth Buffer, so OpenGL is sure about which triangle gos ontop of which.
	glEnable(GL_DEPTH_TEST);

	// Camera!
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	

	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		
		processInput(window); // FunnyInput

		// RENDER COMMANDS GO HERE:
		
		// Specify the color of the background
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f); //state-setting function
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using function
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
		
		// Bind texture to main object
		toaster.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitve
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); //this specifys the primitive we wanna use, the amount of indices we wanna draw, the data type of the indices, and the index of our indecis.

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	toaster.Delete();
	shaderProgram.Delete();



	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the process
	glfwTerminate();
	return 0;
}
