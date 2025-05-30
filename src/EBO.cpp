#include "EBO.h"

// Constructor that generates a elements buffer object and links it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);	// Introduce the vertices into the VBO
}

//bind EBO specifying its a GL_ELEMENT_ARRAY_BUFFER
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

//Bind EBO to 0, to not accidentally modify the created ebo
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Delete now useless Elements Buffer Object
void EBO::Delete() {	
	glDeleteBuffers(1, &ID);
}