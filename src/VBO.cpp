#include"VBO.h"

// Constructor that generates a vertex buffer object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID); // Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID); // Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}

// Bind VBO specifying its a GL_ARRAY_BUFFER
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Bind VBO to 0, to not accidentally modify the created vbo
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Delete now useless Vertext Shader Object
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}