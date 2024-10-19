#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowComponent.cpp"



struct Engine 
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const char* TITLE = "3D GAME ENGINE";
   
   
};


int main(void)
{
    Engine E;
    
    Window win;
    win.SetWindow(E.WIDTH, E.HEIGHT, E.TITLE);
   


}