#include <iostream>
#include "WindowComponent.h"
#include "MathClasses.h"


const int WIDTH = 2560;
const int HEIGHT = 1440;
const char* TITLE = "3D GAME ENGINE";

int main(void)
{
    
    
    Window win;
    win.SetWindow(WIDTH, HEIGHT, TITLE);
    std::cout << "-----------------------------------------------\n" << std::flush;
     
}