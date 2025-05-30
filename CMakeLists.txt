cmake_minimum_required(VERSION 3.16)
project(prismGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to Debug if no build type specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Source files: all cpp + glad.c implementation
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.c
)

# Find GLFW (installed system-wide)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Create executable target
add_executable(prismGL ${SOURCES})

# Include directories for the target
target_include_directories(prismGL PRIVATE
    ${GLFW_INCLUDE_DIRS}            # GLFW headers from pkg-config
    ${CMAKE_SOURCE_DIR}/include     # Your project headers
    ${CMAKE_SOURCE_DIR}/libraries
    # ${CMAKE_SOURCE_DIR}/libraries/glm           # glm headers
)

# Link libraries needed
target_link_libraries(prismGL
    ${GLFW_LIBRARIES}  # GLFW libraries
    dl                 # dynamic linker
    pthread            # threading
    GL                 # OpenGL
)
