#include"VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}

void VBO::Bind() {
	// Bind VBO specifying its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	// Bind VBO to 0, to not accidentally modify the created vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	// Delete now useless Vertext Shader Object
	glDeleteBuffers(1, &ID);
}