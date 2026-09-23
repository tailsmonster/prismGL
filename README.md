# prismGL

Lightweight OpenGL 3D renderer built in C++ as a capstone project for The Marcy Lab School.

<img src="https://nicoaroca.dev/screenshots/prismgl.png" alt="prismGL screenshot" height="300" width="533.5">

## Overview

prismGL is a small graphics project focused on learning low-level rendering fundamentals outside of a web stack. It creates an OpenGL window, loads textures, renders indexed geometry, and implements a movable camera.

The project is now built with CMake and supports Linux, Windows/MSVC, and Windows cross-compilation from Linux with MinGW-w64.

## Tech Stack

- C++20
- OpenGL 3.3
- GLFW
- GLAD
- GLM
- stb_image
- CMake

## Features

- Textured 3D geometry rendered with OpenGL
- Camera movement with frame-rate independent controls
- Mouse-look camera rotation
- Resizable viewport with framebuffer-aware resizing
- Cross-platform CMake builds
- GitHub Actions artifacts for Linux and Windows

## Capstone Presentation Slides
> https://docs.google.com/presentation/d/1KO9wPCWXOwfeYVaQ4cV5OP2ssWn4ZD9pixSIIrQd90w

## Build

### Linux

Install build dependencies, then run:

```bash
cmake --preset linux-release
cmake --build --preset linux-release --config Release
```

Output:

```bash
build/linux-release/bin/prismGL
```

### Windows with Visual Studio

From a Windows machine with Visual Studio 2022 installed:

```powershell
cmake --preset windows-release
cmake --build --preset windows-release --config Release
```

Output:

```powershell
build/windows-release/bin/Release/prismGL.exe
```

### Windows cross-build from Linux

Install MinGW-w64, then run:

```bash
cmake --preset windows-mingw-release
cmake --build --preset windows-mingw-release --config Release
```

Output:

```bash
build/windows-mingw-release/bin/prismGL.exe
```

## Controls

- `W`, `A`, `S`, `D` — Move camera
- `Space` / `Left Ctrl` — Move up/down
- `Left Shift` — Sprint
- `Left Mouse Button` + move mouse — Look around
- `R` — Rename the window
- `Esc` — Close the window

## Notes

- Runtime assets are expected in a `res` directory next to the build output directory.
- The default texture can be replaced by swapping `res/aigis.png` with another PNG using the same filename.


