#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO {
    public:
        // reference ID of the vertex buffer object
        GLuint ID;
        // constructor that generates a vertex buffer and links to it vertices
        VBO(GLfloat* vertices, GLsizeiptr size);

        // binds the vbo
        void Bind();
        // unbinds the vbo
        void Unbind();
        // yeetusdeletus the vbo
        void Delete();
};

#endif