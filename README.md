# "3D Game Engine"

Project that is in progress.

## Current state

- In current state I have implemented basic stuff like Camera movement, input system, rendering, math classes.  
- It is my personal decision to write math classes from scratch(horrible dicision), With a foundational background in Calculus II and Linear Algebra from university,
  I'm looking to deepen my understanding of the mathematics essential for game engines and 3D game development. 
- My rendering class can visually display .obj .mtl with png texture files created in Blender or other 3D modeling software. It has simple graphics pipeline
  that allows my program to view 3D models.
  this class also has simple GLSL file parser to use shaders for coloring or math calculations.
- for now only thing I care about is finishing this project and after that I will absolutely make it portable for linux


  ## Demo

Here’s what the renderer looks like in action:
- Cube
![cubetextured](https://github.com/user-attachments/assets/89a7d88d-14e1-4b42-b8ee-b7ce53aab3ac)




- room
![badtexturedroom](https://github.com/user-attachments/assets/99585d3d-5537-49dd-9a5f-e61e7f4e0fcc)


## Build Instructions
### This project is configured on 32-bit and 64-bit architectures now. you can run this project in VS with both configurations.
1. Clone the repo.
2. Open `_Project_GLFW_.sln` in Visual Studio.
3. Build the project. No external setup needed.
