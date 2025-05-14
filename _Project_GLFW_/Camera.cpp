#include "Camera.h"

//CameraPosition = Vector3F<float>(4.0f, 2.0f, 3.0f);
//CameraTarget = Vector3F<float>(0.0f, 0.0f, 0.0f);
//CameraUp = Vector3F<float>(0.0f, 4.0f, 0.0f);

Camera::Camera()
{
	FOV = 75.0 * PI / 180.0;
	AspectRatio = Width / Height;
	NearPlane = 0.1f;
	FarPlane = 100.0f;
	speed = 10.00;
	Instance = Matrix<float>(4, 4, 1.0f);
	CameraPosition = Vector3F<float>(4.0f, 3.0f, 4.0f);
	CameraTarget += Vector3F<float>(0.0f, 0.0f, -1.0f);
	CameraUp = Vector3F<float>(0.0f, 4.0f, 0.0f);
	
	
	
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
	speed = 0.05f * deltatime;
 
	if (Input::getKey(GLFW_KEY_W)) 
	{
		
		this->CameraPosition += this->CameraTarget * this->speed;
		std::cout << "CameraPosition: " << this->CameraPosition << "\n";
		std::cout << "W was pressed" << "\n";
	}
	if (Input::getKey(GLFW_KEY_S))
	{
		this->CameraPosition -= this->CameraTarget * this->speed;
		std::cout << "Cameraposition" << this->CameraPosition;
		std::cout << "S was pressed" << "\n";
	}
	if (Input::getKey(GLFW_KEY_A))
	{
		this->CameraPosition -= (this->CameraTarget.crossproduct(this->CameraUp)).normalize3d() * this->speed;
		std::cout << "Cameraposition" << this->CameraPosition;
		std::cout << "A was pressed" << "\n";
	}
	if (Input::getKey(GLFW_KEY_D))
	{
		this->CameraPosition += (this->CameraTarget.crossproduct(this->CameraUp)).normalize3d() * this->speed;
		std::cout << "Cameraposition" << this->CameraPosition;
		std::cout << "D was pressed" << "\n";
	}
}


