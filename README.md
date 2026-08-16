# 3D Game Engine

A C++/OpenGL rendering engine built from scratch (including its own math library) as a way to actually keep the linear algebra and calculus I learned in my first year of university, instead of watching it fade the way it does for most students once the exams are over.

## Backstory

When I started my first year of university, I learned C++ alongside linear algebra and calculus. Like most students, I assumed I'd forget most of it the moment the semester ended. 
That bothered me. all that effort just to let it disappear. I wanted to build something that combined the language I liked most with the math I'd just spent a year fighting through, 
but the idea felt too big. Systems programming and "real" math felt out of reach for someone with as little experience as I had, so I shelved it.

A year later, my brother encouraged me to just start and learn as I went rather than waiting to feel ready. 
I found a tutorial series on building a game engine in Java, followed it to get oriented, then found LearnOpenGL and switched over.
The first milestone was a triangle on screen. Then I decided (deliberately) to write my own math library instead of using an existing one like GLM, 
so I'd actually understand the matrices and vectors I was using rather than treating them as a black box.

Moving from 2D to 3D is where it got hard. I spent close to three weeks just trying to get a cube to stop stretching and squashing on screen. 
Eventually I worked through the projection and rotation math, got it rotating correctly with `glfwGetTime()`, and from there kept building outward: texture mapping, 
a first attempt at an OBJ loader (later replaced with a more robust one), and a camera system that took a real fight with Euler angles to get right. 
The result is an engine that loads and renders textured OBJ/MTL models with a first-person camera, running smoothly in real time.

## Current State

- Custom math library (vectors, matrices, transforms) written from scratch to build real intuition for the underlying linear algebra
- OBJ/MTL model loading with multi material batch rendering
- GLSL shader pipeline for coloring and per-vertex/fragment math
- Free-moving camera system (Euler-angle based)
- Real-time rendering loop

## Performance

- Renders textured OBJ/MTL models at steady approximately ~2000 FPS with an active rotating/free camera
- Tested on: [RTX 3050 8gb]

## Demo

<img width="800" height="450" alt="niva-ezgif com-optimize" src="https://github.com/user-attachments/assets/da98c071-2a18-425e-ae47-10a6a41c26ed" />

## Niva Lada 2121 FBX model is from sketchfab Made by Greg McKechnie

## Assets used
You can find Assets used such as obj/mtl models, textures pngs, shaders, skyboxes. in path _Project_GLFW_/TOOLS/

## Roadmap

- Linux portability
- lighting
- FBX importing
- AABB collision detection
- IMGUI integretion

## Build Instructions

This project is configured for 32-bit and 64-bit architectures. *currently works only in Visual Studio

1. Clone the repo.
2. Open `_Project_GLFW_.sln` in Visual Studio.
3. Build the project. No external setup needed.
