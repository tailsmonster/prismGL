#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <glad/glad.h> // or your GL loader

class Shader {
public:
    GLuint ID;

    Shader();            // No more file path arguments!
    void Activate();
    void Delete();

private:
    void compileErrors(unsigned int shader, const char* type);
};

#endif
