#include "Camera.h"

//TODO camera rotation by mouse

bool firstMouse = true;
float lastX = Width / 2.0f;
float lastY = Height / 2.0f;

float yaw = -89.0f;
float pitch = 89.0f;


Camera::Camera()
{
	m_FOV = 75.0 * PI / 180.0;
	m_AspectRatio = static_cast<float>(Width) / Height;
	m_NearPlane = 0.1f;
	m_FarPlane = 100.0f;
	m_Speed = 10.00;
	m_Instance = Matrix<float>(4, 4, 1.0f);
	m_CameraPosition = Vector3F<float>(4.0f, 3.0f, 4.0f);
	m_CameraTarget += Vector3F<float>(0.0f, 0.0f, -1.0f);
	m_CameraUp = Vector3F<float>(0.0f, 4.0f, 0.0f);

}

double Camera::getFov() const
{
	return m_FOV;
}

float Camera::getAspectRatio() const
{
	return m_AspectRatio;
}

float Camera::getNearPlane() const
{
	return m_NearPlane;
}

float Camera::getFarPlane() const
{
	return  m_FarPlane;
}

double Camera::getSpeed() const
{
	return m_Speed;
}

Vector3F<float>& Camera::getCameraPosition() 
{
	return m_CameraPosition;
}

Vector3F<float> Camera::getCameraTarget() const
{
	
	return m_CameraTarget;
}

Vector3F<float> Camera::getCameraUp() const
{
	return m_CameraUp;
}

double Camera::setSpeed(double s_speed)
{
	return this->m_Speed=s_speed;
}

Matrix<float> Camera::getLookat(const Vector3F<float>& CameraP, const Vector3F<float>& CameraT, const Vector3F<float>& CameraU) 
{
	
	return m_Instance.LookOfCamera(CameraP, CameraT, CameraU);
}

Matrix<float> Camera::getProjection(const double& fov,const float& aspectRatio, const float& nearplane, const float& farplane)
{
	return m_Instance.Projection(fov,aspectRatio,nearplane,farplane);
}

void Camera::InputValidation(float deltatime)
{
	//to process cameramovement in time
	float position_y = m_CameraPosition.getY3D();
	m_Speed = 5.0f* deltatime;

	Vector3F<float> forward = (m_CameraTarget - m_CameraPosition).Normalize3d();
	Vector3F<float> right = forward.CrossProduct(m_CameraUp).Normalize3d();
	if (Input::getKey(GLFW_KEY_W)) 
	{
		
		m_CameraPosition += forward * m_Speed;
		m_CameraTarget += forward * m_Speed;
		
	}
	if (Input::getKey(GLFW_KEY_S))
	{
		
		m_CameraPosition -= forward * m_Speed;
		m_CameraTarget -= forward * m_Speed;
		
	}
	if (Input::getKey(GLFW_KEY_A))
	{
		m_CameraPosition += right * m_Speed;
		m_CameraTarget += right * m_Speed;
		
	}
	if (Input::getKey(GLFW_KEY_D))
	{
		m_CameraPosition -= right * m_Speed;
		m_CameraTarget -= right * m_Speed;
		
	}
	if (Input::getKey(GLFW_KEY_E))
	{
		
		//add y s 
		position_y += m_Speed;
		m_CameraPosition.setY3D(position_y);
		float target_y = m_CameraTarget.getY3D();
		m_CameraTarget.setY3D(target_y + m_Speed);
	}
	if (Input::getKey(GLFW_KEY_Q))
	{
		//sub y s
		position_y -= m_Speed;
		m_CameraPosition.setY3D(position_y);
		float target_y = m_CameraTarget.getY3D();
		m_CameraTarget.setY3D(target_y - m_Speed);
	}
	
}

void Camera::MouseMovement(float deltatime)
{

	static bool wasPressed = false;
	bool isPressed = Input::getMouseKey(GLFW_MOUSE_BUTTON_LEFT);

	if (isPressed && !wasPressed) 
	{	 
		firstMouse = true;   
	}

	wasPressed = isPressed;
	Vector3F<float> forward = (m_CameraTarget - m_CameraPosition).Normalize3d();
	Vector3F<float> right = forward.CrossProduct(m_CameraUp).Normalize3d();	
	if (isPressed)
	{
		glfwSetInputMode(Window::m_mywindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		Vector2F<double>mousepositions;
		mousepositions = Vector2F<double>::CursorPos();
		 
		float xpos = mousepositions.get_X();
		float ypos = mousepositions.get_Y();

		if (firstMouse) {

			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
	
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;
		// this code saves camera for gimbal lock 
		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}
		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
		float r_Yaw = yaw * ToRadians;
		float r_Pitch = pitch * ToRadians;
		Vector3F<float> direction;
		direction.setX3D(cos(r_Yaw) * cos(r_Pitch));
		direction.setY3D(sin(r_Pitch));
		direction.setZ3D(sin(r_Yaw) * cos(r_Pitch));
		forward = direction.Normalize3d();
		m_CameraTarget = m_CameraPosition + forward;	
		
	}
	else {
		glfwSetInputMode(Window::m_mywindow, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
	}
	
}


