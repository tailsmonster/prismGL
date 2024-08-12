#include"VAO.h"

// constructor that generates vao id
VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO& VBO, GLuint layout) {
    VBO.Bind();
    // Configure the Vertex Attribute so that OpenGL knows how read the VBO
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 /* <- weird pointer void for our offset, usually a pointer to where our vertices begin in an array*/);
    // Enable the Vertex Attribute so that OpenGL knows how to use it 
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind() {
    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    // Bind VAO to 0 to not accidentally modify the Vertex Array Object
    glBindVertexArray(0);
}

void VAO::Delete() {
    // Delete now useless Vertex Array Object
    glDeleteVertexArrays(1, &ID);
}