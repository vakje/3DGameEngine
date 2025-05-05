#include "Camera.h"



Camera::Camera()
{
	FOV = 75.0 * PI / 180.0;
	AspectRatio = Width / Height;
	NearPlane = 0.1f;
	FarPlane = 100.0f;
	speed = 10.00;
	CameraPosition = Vector3F<float>(4.0f, 2.0f, 3.0f);
	CameraTarget = Vector3F<float>(0.0f, 0.0f, 0.0f);
	CameraUp = Vector3F<float>(0.0f, 4.0f, 0.0f);
	Instance = Matrix<float>(4, 4, 1.0f);
}

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

Vector3F<float> Camera::Get_CameraPosition() const
{
	return CameraPosition;
}

Vector3F<float> Camera::Get_CameraTarget() const
{
	return CameraTarget;
}

Vector3F<float> Camera::Get_CameraUp() const
{
	return CameraUp;
}

Matrix<float> Camera::Get_Lookat(const Vector3F<float>& CameraP, const Vector3F<float>& CameraT, const Vector3F<float>& CameraU) 
{

	return Instance.LookOfCamera(CameraP, CameraT, CameraU);
}

Matrix<float> Camera::Get_Projection(const double& fov,const float& aspectRatio, const float& nearplane, const float& farplane)
{
	return Instance.Projection(fov,aspectRatio,nearplane,farplane);
}

void Camera::InputValidation()
{
	//to process cameramovement in time
	float deltatime = 0.0f;
	float lastframe = 0.0f;
	float currentframe = glfwGetTime();
	deltatime = currentframe - lastframe;
	lastframe = currentframe;
	speed = 2.5f * deltatime;

	if (Input::getKey(GLFW_KEY_W)) 
	{
		CameraPosition += CameraTarget * speed;
		std::cout << "W was pressed" << "\n";
	}
	if (Input::getKey(GLFW_KEY_S))
	{
		CameraPosition -= CameraTarget * speed;
		std::cout << "S was pressed" << "\n";
	}
	if (Input::getKey(GLFW_KEY_A))
	{
		CameraPosition -= (CameraTarget.crossproduct(CameraUp)).normalize3d() * speed;
		std::cout << "A was pressed" << "\n";
	}
	if (Input::getKey(GLFW_KEY_D))
	{
		CameraPosition += (CameraTarget.crossproduct(CameraUp)).normalize3d() * speed;
		std::cout << "D was pressed" << "\n";
	}
}


