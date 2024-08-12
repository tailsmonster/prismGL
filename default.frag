// Fragment Shader Source code
#version 330 core
out vec4 FragColor;

// Inputs color to vertex shader
in vec3 color; 
// Inputs the texture coordinates from the vertex shader
in vec2 textCoord;

// gets the texture unit from the main function
uniform sampler2D tex0;

void main() 
{
  // FragColor = vec4(color, 1.0f);
  FragColor = texture(tex0, textCoord);
};