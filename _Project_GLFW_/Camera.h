#pragma once
#include "MathClasses.h"
#include "InputSystem.h"

class Camera 
{
private:
    double FOV;
    float AspectRatio;
    float NearPlane;
    float FarPlane;
    double speed;
   
    Vector3F<float> Position;
    Vector3F<float> Target;
    Vector3F<float> up;
    
public:
    Camera(double Fov , float ascpectRatio , float NearPlane, float farplane , double speed);
    double Get_Fov()const;
    float Get_AspectRatio()const;
    float Get_NearPlane()const;
    float Get_FarPlane()const;
    double Get_Speed()const;
    Vector3F<float> Get_Position()const;
    Vector3F<float> Get_Target()const;
    Vector3F<float> Get_Up()const;
    

};