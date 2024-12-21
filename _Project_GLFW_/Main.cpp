
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
    try {
        Matrix<int> m1(4, 4, 1);

        m1.initidentity();
        std::cout << m1;
        Matrix<double> m2(3, 3, 1.0);
        std::cout << "-------------------PITCH---------------------- \n" << std::flush;
        m2.PitchRotation(30.0);
        std::cout << m2 << "\n";
        Matrix<double> M1(m2);
        std::cout << "cheching copy constructor again" << std::flush;
        std::cout << M1;
        std::cout << "-------------------YAW---------------------- \n" << std::flush;
        Matrix<double> M2(3, 3, 1.0);

        M2.YawRotation(30.0);
        std::cout << M2;
        std::cout << "-------------------ROLL---------------------- \n" << std::flush;
        Matrix<double> M3(3, 3, 1.0);
        M3.RollRotation(30.0);
        std::cout << M3;
        std::cout << "-------------------FINISH--------------------- \n" << std::flush;
    }
    catch (std::exception ex) { std::cerr << "some:" << ex.what() << std::endl; }
    

   
}