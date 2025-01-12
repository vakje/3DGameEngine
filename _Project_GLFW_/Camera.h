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
    
public:
    Camera(double Fov , float ascpectRatio , float NearPlane, float farplane , double speed );
    double Get_Fov()const;
    float Get_AspectRatio()const;
    float Get_NearPlane()const;
    float Get_FarPlane()const;
    double Get_Speed()const;

};