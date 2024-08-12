#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/std_image.h>

#include"shaderClass.h"
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"

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

// Vertices Coordinates for Triangle
GLfloat triVertices[] = {
	//               COORDS                     /      COLORS            //
	-0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f,  0.3f,  0.02f,  // Lower Left Corner
	 0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,   0.5f,  0.65f, 0.4f,   // Lower Right Corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   1.0f,  0.43f, 0.32f,  // Upper Corner
	-0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,   0.9f,  0.56f, 0.69f,  // Inner Left
	 0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,   0.63f, 0.2f,  0.15f,  // Inner Right
	 0.0f, -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f,  0.3f,  0.02f,  // Inner Down
};												                  
// start index buffer wahooie!
GLuint triIndices[] = {
	0,3,5, //Lower left tri
	3,2,4, //lower right tri
	5,4,1 //top tri
};



//SQUARE :D
GLfloat vertices[] = {
	//    COORDS              /      COLORS    /              MAPPING   //
	-0.5f, -0.5f,  0.0f,       1.0f,  0.0f, 0.0f,       0.0f, 0.0f, // Lower Left Corner
	-0.5f,  0.5f,  0.0f,       0.0f,  1.0f, 0.0f,       0.0f, 1.0f, // Upper Left Corner
	 0.5f,  0.5f,  0.0f,       0.0f,  0.0f, 1.0f,       1.0f, 1.0f, // Upper Right Corner
	 0.5f, -0.5f,  0.0f,       1.0f,  1.0f, 1.0f,       1.0f, 0.0f, // Lower Left Corner
};
GLuint indices[] = {
	0, 2, 1, // Upper Tri
	0, 3, 2  // Lower Triangle
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
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("aigis.png", &widthImg, &heightImg, &numColCh, 0);

	//the texture object itself
	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// here we choose nearest neighbor or linear.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	// repeating wahooie
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//gl plan to order
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor};

	// gen texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	/*
	The most common color channels are 
	GL_RGBA -> JPEG files
	GL_RGB -> PNG files
	*/

	// texture uniform
	GLuint tex0Uniform = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();


	// Specify the color of the background
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //state-setting function
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT); //state-using function
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);



	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		// user input
		processInput(window);

		// render commands go here:
		// Specify the color of the background
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f); //state-setting function
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT); //state-using function
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		glUniform1f(uniformID, 0.5f);
		// Bind texture to main object
		glBindTexture(GL_TEXTURE_2D, texture);
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitve
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //this specifys the primitive we wanna use, the amount of indices we wanna draw, the data type of the indices, and the index of our indecis.

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();



	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the process
	glfwTerminate();
	return 0;
}
