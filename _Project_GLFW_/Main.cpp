#include <iostream>
#include "WindowComponent.h"



const int WIDTH = 1920;
const int HEIGHT = 1080;
const char* TITLE = "3D GAME ENGINE";
   




int main(void)
{
    
    
    Window win;
    win.SetWindow(WIDTH, HEIGHT, TITLE);
    std::cout << "-----------------------------------------------\n" << std::flush;
   
    
}