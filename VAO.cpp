#include"VAO.h"

// constructor that generates vao id
VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset/* (void*)0  <- weird pointer void for our offset, usually a pointer to where our vertices begin in an array*/); // Configure the Vertex Attribute so that OpenGL knows how read the VBO
    glEnableVertexAttribArray(layout);    // Enable the Vertex Attribute so that OpenGL knows how to use it 
    VBO.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(ID); // Make the VAO the current Vertex Array Object by binding it
}

void VAO::Unbind() {
    glBindVertexArray(0);  // Bind VAO to 0 to not accidentally modify the Vertex Array Object
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID); // Delete now useless Vertex Array Object
}