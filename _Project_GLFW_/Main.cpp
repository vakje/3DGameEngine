
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
   
    Vector2F<int> v1(2.0, 3.0);
    Vector2F<int> v2(4.0, 5.0);
    int scalar = 2.0;

    // 1. Vector Addition (element-wise)
    Vector2F<int> resultAdd = v1 + v2; // Adds each component of v1 and v2
    std::cout << "v1 + v2 = " << resultAdd << "\n";

    v1 += v2;
    std::cout << "v1 += v2 = " << v1 << "\n";
    // 2. Vector Subtraction (element-wise)
    Vector2F<int> resultSub = v1 - v2; // Subtracts each component of v2 from v1
    std::cout << "v1 - v2 = " << resultSub << "\n";
    v1 -= v2;
    std::cout << "v1 -= v2 = " << v1 << "\n";
    // 3. Scalar Addition
    Vector2F<int> resultAddScalar = v1 + scalar; // Adds scalar to each component of v1
    std::cout << "v1 + scalar = " << resultAddScalar << "\n";

    // 4. Scalar Subtraction
    Vector2F<int> resultSubScalar = v1 - scalar; // Subtracts scalar from each component of v1
    std::cout << "v1 - scalar = " << resultSubScalar << "\n";

    // 5. Scalar Multiplication
    Vector2F<int> resultMulScalar = v1 * scalar; // Multiplies each component of v1 by scalar
    std::cout << "v1 * scalar = " << resultMulScalar << "\n";

    // 6. Element-Wise Multiplication
    Vector2F<int> resultElemWiseMul = v1 * v2; // Multiplies each component of v1 and v2
    std::cout << "v1 * v2 (element-wise) = " << resultElemWiseMul<<"\n";

    v1 *= v2;
    std::cout << "v1 *= v2  = " << v1 << "\n";
    // 7. Dot Product
    int dotProduct = v1.dotproduct(v2); // Computes the dot product of v1 and v2
    std::cout << "v1 dot v2 = " << dotProduct << "\n";
    
    // Rotate check
    Vector2F<int> myvec(10.0, 22.5);
    myvec = myvec.Rotate(45.0);
    std::cout<< "After rotation:" << myvec <<"\n";
    
    // division check
    Vector2F<int> resultdiv = v1 / v2;
    std::cout << "v1 / v2 (element-wise) = " << resultdiv << "\n";

    Vector2F<int> resultdivelementwise = v1 / scalar;
    std::cout << "v1 / v2  = " << resultdivelementwise << "\n";

    v1/=v2;
    std::cout << "v1 /= v2 (element-wise) = " << v1 << "\n";

    std::cout << "----------------------------------------------- \n" << std::flush;

    Vector3F<int> vec1(2.0, 3.0, 3.0);
    Vector3F<int> vec2(4.0, 5.0, 5.0);
    

    // 1. Vector Addition (element-wise)
    Vector3F<int> resultAdd3d = vec1 + vec2; // Adds each component of v1 and v2
    std::cout << "v1 + v2 = " << resultAdd3d << "\n";

    vec1 += vec2;
    std::cout << "v1+=v2 " << vec1 << "\n";
    // 2. Vector Subtraction (element-wise)
    Vector3F<int> resultSub3d = vec1 - vec2; // Subtracts each component of v2 from v1
    std::cout << "v1 - v2 = " << resultSub3d << "\n";

    vec1 -= vec2;
    std::cout << "v1 -= v2  " << vec1 << "\n";
    // 3. Scalar Addition
    Vector3F<int> resultAddScalar3d = vec1 + scalar; // Adds scalar to each component of v1
    std::cout << "v1 + scalar = " << resultAddScalar3d << "\n";

    // 4. Scalar Subtraction
    Vector3F<int> resultSubScalar3d = vec1 - scalar; // Subtracts scalar from each component of v1
    std::cout << "v1 - scalar = " << resultSubScalar3d << "\n";

    // 5. Scalar Multiplication
    Vector3F<int> resultMulScalar3d = vec1 * scalar; // Multiplies each component of v1 by scalar
    std::cout << "v1 * scalar = " << resultMulScalar3d << "\n";

    // 6. Element-Wise Multiplication
    Vector3F<int> resultElemWiseMul3d = vec1 * vec2; // Multiplies each component of v1 and v2
    std::cout << "v1 * v2 (element-wise) = " << resultElemWiseMul3d << "\n";

    vec1 *= vec2;
    std::cout << "v1 *= v2" << vec1 << "\n";
    // 7. Dot Product
    int dotProduct3d = vec1.dotproduct(vec2); // Computes the dot product of v1 and v2
    std::cout << "v1 dot v2 = " << dotProduct3d << "\n";

    std::cout << "----------------------------------------------- \n" << std::flush;

    std::cout << "checking copy constructor and assignment operator\n";
    Vector2F<int> v11(v2);
    std::cout << v11 << "this is the copy contructor of Vector2F\n";
    Vector2F<int> VEC1(2, 2);
   
    v1 = VEC1;
    std::cout << v1 << "this is the assignment operator of Vector2F\n";
    
    Vector3F<int> vec11(vec2);
    std::cout << vec11 << "this is the copy contructor of Vector3F\n";
    Vector3F<int> VEC(2,2,2);
    vec1 = VEC;

    std::cout << vec1 << "this is the assignment operator of Vector2F\n";

    std::cout << "----------------------------------------------- \n" << std::flush;


}