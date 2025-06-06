# prismGL
### _My Capstone Project for The Marcy Lab School_
*A lightweight OpenGL-based 3D graphics application built from scratch in C++*

As a part of our Software Engineering Fellowship, we had 10 weeks to learn a brand new technology and create a capstone project with it.
I decided to diverge from the web development I'd have spent the last 10 months learning to dive deeper into low-level programming. I've always been fascinated with game development, and making *something* in that realm was my main motivator behind going down this route. I started out by learning **C**, and once I had a handle on the basics I moved onto picking up **C++**. Eventually came time to pick up **OpenGL** (a graphics library I had chosen for being an industry standard) and used that alongside **GLFW** to manage windows and OpenGL contexts, **Glad** to manage function pointers for OpenGL, and later incorporated **GLM**, a C++ math library for OpenGL's shading language.

While this is a small project, it shows a commitment to self learning! This project was tough for me! But I was able to pull through, and learn so many new concepts in such a short amount of time.

<!-- ![Screenshot](https://github.com/tailsmonster/portfolio/blob/main/vite-project/src/assets/static/screenshots/prismgl.png?raw=true) -->
<img src="https://github.com/tailsmonster/portfolio/blob/main/vite-project/src/assets/static/screenshots/prismgl.png?raw=true" alt="screenshot" height="300" width="168">

Presentation Slides: https://docs.google.com/presentation/d/1KO9wPCWXOwfeYVaQ4cV5OP2ssWn4ZD9pixSIIrQd90w

This was originally built on Windows 10 on Visual Studio, but I had issues compiling a release executable. Since I use Linux 24/7 nowadays, I've made it to now compile with only CMake, making it crossplatform and portable, also squashing any bugs I didn't resolve previously. I mostly just did this to have an actual binary to share, for portfolio purposes.

---

### BUILDING

Dependencies:
- CMake
- C++17
- OpenGL 3.3+
- GLFW 
- GLM

Linux:
```bash
$ mkdir build && cd build
$ cmake ..
$ make
```

Windows:

```powershell
COMING SOON
```

### CONTROLS

- `W, A, S, D` — Move camera

- `Mouse Left Button` + Move — Look around

- `Space / Left Ctrl` — Move up/down

- `Left Shift` — Increase movement speed

- `ESC` — Close the window

- `R`  — Rename the window

> Technically, you can replace aigis.png with any file of the same name. So, you can add your own custom png texture this way!
