cmake_minimum_required(VERSION 3.10)
project(OpenGL_Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    Main.cpp
    shaderClass.cpp
    VBO.cpp
    EBO.cpp
    VAO.cpp
    Texture.cpp
    Camera.cpp
)

# Add header files
set(HEADERS
    ./shaderClass.h
    ./VBO.h
    ./EBO.h
    ./VAO.h
    ./Texture.h
    ./Camera.h
)

# Set paths for local libraries
include_directories(include/glad)
include_directories(include/glfw)
include_directories(include/glm)
include_directories(include/stb)


# Create main executable
add_executable(prismGL ${SOURCES})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link system libraries and GLFW (assuming it's dynamically linked)
target_link_libraries(prismGL OpenGL::GL glfw dl pthread X11)


