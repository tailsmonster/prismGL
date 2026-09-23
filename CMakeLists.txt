cmake_minimum_required(VERSION 3.16)

project(prismGL VERSION 1.0.1 LANGUAGES C CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(PRISMGL_USE_SYSTEM_GLFW "Use an installed GLFW package instead of downloading GLFW" OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

find_package(OpenGL REQUIRED)

if(PRISMGL_USE_SYSTEM_GLFW)
    find_package(glfw3 CONFIG QUIET)

    if(NOT TARGET glfw)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GLFW3 REQUIRED IMPORTED_TARGET glfw3)
        add_library(glfw ALIAS PkgConfig::GLFW3)
    endif()
else()
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(glfw)
endif()

set(PRISMGL_SOURCES
    src/Camera.cpp
    src/EBO.cpp
    src/glad.c
    src/Main.cpp
    src/shaderClass.cpp
    src/stb.cpp
    src/Texture.cpp
    src/VAO.cpp
    src/VBO.cpp
)

add_executable(prismGL ${PRISMGL_SOURCES})

target_include_directories(prismGL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
)

target_link_libraries(prismGL PRIVATE
    glfw
    OpenGL::GL
)

if(MSVC)
    target_compile_options(prismGL PRIVATE /W4 /permissive-)
else()
    target_compile_options(prismGL PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -Wpedantic>)
endif()

if(MINGW)
    target_link_options(prismGL PRIVATE -static -static-libgcc -static-libstdc++)
endif()

set_target_properties(prismGL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${config}" config_upper)
    set_target_properties(prismGL PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_BINARY_DIR}/bin/${config}
    )
endforeach()

add_custom_command(TARGET prismGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/res
            $<TARGET_FILE_DIR:prismGL>/../res
    COMMENT "Copying runtime resources"
)
