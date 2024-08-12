#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
    public:
        // creates id for vector array object
        GLuint ID;
        // constructor that generates vao id
        VAO();
        
        // Links a VBO to VAO using a certain layout
        void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);//yay shaders
        // Binds the vao
        void Bind();
        // unbinds the vao
        void Unbind();
        // deletes the vao
        void Delete();
};


#endif