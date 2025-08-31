#pragma once
#include "MathClasses.h"
#include "InputSystem.h"

class Camera
{
private:
    double m_FOV;
    float m_AspectRatio;
    float m_NearPlane;
    float m_FarPlane;
    double m_Speed;
    double m_RotSpeed;
    Matrix<float> m_Instance;
    Vector3F<float> m_CameraPosition;
    Vector3F<float> m_CameraTarget;
    Vector3F<float> m_CameraUp;
 



    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = Width / 2.0f;
    float lastY = Height / 2.0f;
    bool firstMouse = true;
    
public:
   
    Camera();

    //camera's perspective(view)
    double getFov() const;
    float getAspectRatio() const;
    float getNearPlane() const;
    float getFarPlane() const;

    double getSpeed() const;
    double getRotSpeed()const;
    //camera's movement positions ..
    Vector3F<float>& getCameraPosition();
    Vector3F<float> getCameraTarget()const;
    Vector3F<float> getCameraUp()const;
 

    double setSpeed(double s_speed);
public:

    //projection tools
    Matrix<float> getLookat(const Vector3F<float>& CameraP, const Vector3F<float>& CameraT, const Vector3F<float>& CameraU);
    Matrix<float> getProjection(const double& fov, const float& aspectRatio, const float& nearplane, const float& farplane);

    void InputValidation(float deltatime);
    void MouseMovement(float deltatime);

};

