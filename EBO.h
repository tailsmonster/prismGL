#pragma once


#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "include/glad/glad.h"

class EBO {
public:
    // id reference for elements buffer object
    GLuint ID;
    // constructor that generates a Elements Buffer Object and links the indices
    EBO(GLuint* indices, GLsizeiptr size);

    // binds ebo
    void Bind();
    // unbinds ebo
    void Unbind();
    // deletes ebo
    void Delete();
};

#endif