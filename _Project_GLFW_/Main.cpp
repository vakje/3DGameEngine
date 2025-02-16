#include <iostream>
#include "WindowComponent.h"
#include "Mainobject.h"


const int WIDTH = 1920;
const int HEIGHT = 1080;
const char* TITLE = "3D GAME ENGINE";
   




int main(void)
{
    
    
    Window win;
    win.SetWindow(WIDTH, HEIGHT, TITLE);
    std::cout << "----------------------------------------------- \n" << std::flush;
   
    Object obj("object1", "Cube.obj");
    obj.objfileparser(obj.get_path());
    
}