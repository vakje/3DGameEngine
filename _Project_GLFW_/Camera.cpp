#include "Camera.h"

Camera::Camera(double Fov = 75.0 * PI / 180.0, float ascpectRatio = Width / Height, float NearPlane = 0.1f, float farplane = 100.0f, double speed = 10.00)
:FOV(Fov), AspectRatio(ascpectRatio), NearPlane(NearPlane), FarPlane(farplane),speed(speed) {}

double Camera::Get_Fov() const
{
	return FOV;
}

float Camera::Get_AspectRatio() const
{
	return AspectRatio;
}

float Camera::Get_NearPlane() const
{
	return NearPlane;
}

float Camera::Get_FarPlane() const
{
	return  FarPlane;
}

double Camera::Get_Speed() const
{
	return speed;
}
