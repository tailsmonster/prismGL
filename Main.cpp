#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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


// Vertex Shader Source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment Shader Source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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



	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Vertices Coordinates for Triangle
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Lower Left Corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  //Lower Right Corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper Corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner Left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner Right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Inner Down
	};
	// start index buffer wahooie!
	GLuint indices[] = {
		0,3,5, //Lower left tri
		3,2,4, //lower right tri
		5,4,1 //top tri
	};


	// Create reference containers for the Vertex Array Object (VAO) and the Vertex Buffer Object (VBO)
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 /* <- weird pointer void for our offset, usually a pointer to where our vertices begin in an array*/);
	// Enable the Vertex Attribute so that OpenGL knows how to use it 
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO or the VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// Specify the color of the background
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f); //state-setting function
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
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f); //state-setting function
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT); //state-using function

		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitve
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //this specifys the primitive we wanna use, the amount of indices we wanna draw, the data type of the indices, and the index of our indecis.

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);



	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the process
	glfwTerminate();
	return 0;
}
