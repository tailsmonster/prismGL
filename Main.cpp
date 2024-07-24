#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window) {
	// Here, we have a void function that takes in a pointer to our window.

	// This if statement checks if the escape key is pressed, and when it is the window is closed.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// This if statement checks if the r key is pressed, and when it is the window is renamed.
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		glfwSetWindowTitle(window, "I HAVE NO IDEA WHAT I'M DOING!!!!!!\n");
	}
}



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
	GLFWwindow* window = glfwCreateWindow(600, 600, "First OpenGL Project", NULL, NULL);
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
	glViewport(0, 0, 600, 600);


	// Get some input control in GLFW. This function returns which key is being pressed.


	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		// user input
		processInput(window);

		// render commands go here:
		// Specify the color of the background
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f); //state-setting function
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT); //state-using function




		// Take care of all GLFW events
		glfwPollEvents();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the process
	glfwTerminate();
	return 0;
}

