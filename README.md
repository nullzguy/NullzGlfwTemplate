# - NullzGlfwTemplate -

A C++, glfw, imgui template.\
Made for both lightweight tests, and massive projects.

## Requirements

- CMake 3.20 or higher
- C++ compiler with C++17 support
- JetBrains Rider (or any CMake-capable IDE)
- OpenGL 4.1 compatible GPU/driver (compatibility profile)
- GLFW 3.3 or higher
- GLM

GLAD is bundled in `external/glad` and is loaded automatically at engine startup.
ImGui is fetched by CMake and does not need to be installed manually.

## Building and Running

1. Open the project in Rider
2. Use the Run/Debug buttons to build and execute the project

## About this project
##### Greets!

When i was 12, i was always thinking about making little projects, such as\
fluid simulations, cryptography, maths, physics, body simulations, and other stuff.\
I honestly find it very inspiring and interesting.\
But i found engines like Unity pretty overkill and bloaty.

Thats why after some time, i decided to create my own little template, this one.\
I consider this a little engine actually. I am actively working on it, until you can create little tests, simulations, and massive projects, with ease, all with code, and *almost* zero bloat!

The philosophy is about making everything simple and clean - by using functions and multiple files.

## DONE
- Added simple inputs support
- Added ticking system limitation control just like framerate does
- Added a full gpu communication pipeline
- Remade simulation resolution logic
- Fixed unlocked TPS stalling
- Synchronized the rendering resolution with window resolution
- Did a lot of refactoring overall
- Tidied the directories up to multiple sections

## TODO
- Make shader files be put into the compiled binary
- Add fences
- Add audio pipeline
- Add file importing and exporting
- Do some optimizations maybe..?