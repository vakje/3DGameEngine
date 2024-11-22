
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowComponent.h"
#include "InputSystem.h"




struct WindowConfig 
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const char* TITLE = "3D GAME ENGINE";
   
   
};


int main(void)
{
    WindowConfig E;
    
    Window win;
    win.SetWindow(E.WIDTH, E.HEIGHT, E.TITLE);
    std::cout << "----------------------------------------------- \n" << std::flush;
  
   
}