
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
   
    Vector2F v1(2.0, 3.0);
    Vector2F v2(4.0, 5.0);
    double scalar = 2.0;

    // 1. Vector Addition (element-wise)
    Vector2F resultAdd = v1 + v2; // Adds each component of v1 and v2
    std::cout << "v1 + v2 = " << resultAdd << "\n";

    // 2. Vector Subtraction (element-wise)
    Vector2F resultSub = v1 - v2; // Subtracts each component of v2 from v1
    std::cout << "v1 - v2 = " << resultSub << "\n";

    // 3. Scalar Addition
    Vector2F resultAddScalar = v1 + scalar; // Adds scalar to each component of v1
    std::cout << "v1 + scalar = " << resultAddScalar << "\n";

    // 4. Scalar Subtraction
    Vector2F resultSubScalar = v1 - scalar; // Subtracts scalar from each component of v1
    std::cout << "v1 - scalar = " << resultSubScalar << "\n";

    // 5. Scalar Multiplication
    Vector2F resultMulScalar = v1 * scalar; // Multiplies each component of v1 by scalar
    std::cout << "v1 * scalar = " << resultMulScalar << "\n";

    // 6. Element-Wise Multiplication
    Vector2F resultElemWiseMul = v1 * v2; // Multiplies each component of v1 and v2
    std::cout << "v1 * v2 (element-wise) = " << resultElemWiseMul<<"\n";

    // 7. Dot Product
    double dotProduct = v1.dotproduct(v2); // Computes the dot product of v1 and v2
    std::cout << "v1 dot v2 = " << dotProduct << "\n";

    Vector2F myvec(10.0, 22.5);
    myvec = myvec.Rotate(45.0);
    std::cout << myvec << std::endl;


    Vector3F vec1(2.0, 3.0, 3.0);
    Vector3F vec2(4.0, 5.0, 5.0);
    

    // 1. Vector Addition (element-wise)
    Vector3F resultAdd3d = vec1 + vec2; // Adds each component of v1 and v2
    std::cout << "v1 + v2 = " << resultAdd3d << "\n";

    // 2. Vector Subtraction (element-wise)
    Vector3F resultSub3d = vec1 - vec2; // Subtracts each component of v2 from v1
    std::cout << "v1 - v2 = " << resultSub3d << "\n";

    // 3. Scalar Addition
    Vector3F resultAddScalar3d = vec1 + scalar; // Adds scalar to each component of v1
    std::cout << "v1 + scalar = " << resultAddScalar3d << "\n";

    // 4. Scalar Subtraction
    Vector3F resultSubScalar3d = vec1 - scalar; // Subtracts scalar from each component of v1
    std::cout << "v1 - scalar = " << resultSubScalar3d << "\n";

    // 5. Scalar Multiplication
    Vector3F resultMulScalar3d = vec1 * scalar; // Multiplies each component of v1 by scalar
    std::cout << "v1 * scalar = " << resultMulScalar3d << "\n";

    // 6. Element-Wise Multiplication
    Vector3F resultElemWiseMul3d = vec1 * vec2; // Multiplies each component of v1 and v2
    std::cout << "v1 * v2 (element-wise) = " << resultElemWiseMul3d << "\n";

    // 7. Dot Product
    double dotProduct3d = vec1.dotproduct(vec2); // Computes the dot product of v1 and v2
    std::cout << "v1 dot v2 = " << dotProduct3d << "\n";

   

}