// Vertex Shader Source code
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// Outputs color for fragment shader
out vec3 color;
// outpiuts texture coords for fragment shader
out vec2 textCoord;

// controls scale of vertices
uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main()
{
    // Outputs the positions / coords of all vertices
    // gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    // assigns the colors from the vertex data to "color"
    color = aColor;
    // assigns the texture coordinates from the vertex data to "texCoord"
    textCoord = aTex;
};