
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowComponent.h"
#include "InputSystem.h"


const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "3D GAME ENGINE";
   
   



int main(void)
{
    
    
    Window win;
    win.SetWindow(WIDTH, HEIGHT, TITLE);
    std::cout << "----------------------------------------------- \n" << std::flush;
    try {
        Matrix<int> m1(3, 3, 1);

        m1.initidentity(3);
        std::cout << m1;



       
    }
    catch (std::exception ex) { std::cerr << "exception situation :" << ex.what() << std::endl; }
    

   
}