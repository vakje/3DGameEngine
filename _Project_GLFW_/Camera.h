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
    Matrix<float> Instance;
    Vector3F<float> CameraPosition;
    Vector3F<float> CameraTarget;
    Vector3F<float> CameraUp;
    

public:
    Camera();

    //camera's perspective(view)
    double Get_Fov() const;
    float Get_AspectRatio() const;
    float Get_NearPlane() const;
    float Get_FarPlane() const;

    double Get_Speed() const;
    //camera's movement positions ..
    Vector3F<float> Get_CameraPosition()const;
    Vector3F<float> Get_CameraTarget()const;
    Vector3F<float> Get_CameraUp()const;
public:

    //projection tools
    Matrix<float> Get_Lookat(const Vector3F<float>& CameraP, const Vector3F<float>& CameraT, const Vector3F<float>& CameraU);

    Matrix<float> Get_Projection(const double& fov, const float& aspectRatio, const float& nearplane, const float& farplane);

    void InputValidation();

};

