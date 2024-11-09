
#include "InputSystem.h"
#include "Util.h"

/// <summary>
/// declaring it before using cause they are static c++ feature ;)
/// </summary>
std::list<int> Input::currentkeys;
std::list<int> Input::pressedkeys;
std::list<int> Input::Releasedkeys;
std::list<int> Input::CurrentMouseKeys;
std::list<int> Input::MousePressed;
std::list<int> Input::MouseReleased;

/// <summary>
/// made class for mousepostioning 
/// constructor which initilizes object 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
Vector2F::Vector2F(double x, double y) : X(x), Y(y) {}

double Vector2F::get_X() const { return X; }
double Vector2F::get_Y() const { return Y; }
void Vector2F::set_X(double x) { X = x; }
void Vector2F::set_Y(double y) { Y = y; }
/// <summary>
/// to string which informating the user 
/// </summary>
/// <returns></returns>
std::string Vector2F::ToString() const {
	return "(" + std::to_string(X) + "," + std::to_string(Y) + ")";
}
/*
---------------------------------------------------------------------
this vector2f and vector3f classes containning basic mathematic opera
tions, which includes operators overloading like *,/,+,- 
also i have functions of calculating length of a vector 
operators for other vectors and other numbers are overloaded 
also rotations for vectors were added and there normalizations 
---------------------------------------------------------------------
*/
double Vector2F::Length_Vector2f()
{
	return sqrt(X * X + Y * Y);
}

double Vector2F::dotproduct(const Vector2F& r)
{
	return X * r.get_X() + Y * r.get_Y();
}

Vector2F Vector2F::operator+(const Vector2F& other)
{
	return Vector2F(X+other.get_X(),Y+other.get_Y());
}

Vector2F Vector2F::operator-(const Vector2F& other)
{
	return Vector2F(X - other.get_X(), Y - other.get_Y());
}
Vector2F Vector2F::operator*(const Vector2F& other)
{
	return Vector2F(X * other.get_X(), Y * other.get_Y());
}



Vector2F Vector2F::operator+(const double& num)
{
	return Vector2F(X + num, Y + num);
}

Vector2F Vector2F::operator-(const double& num)
{
	return Vector2F(X - num, Y - num);
}

Vector2F Vector2F::operator*(const double& num)
{
	return Vector2F(X * num, Y * num);
}

Vector2F Vector2F::Rotate(const double& angle)
{
	double rad = angle * (3.14159265358 / 180);
	double sin = std::sin(rad);
	double cos = std::cos(rad);

	return Vector2F(cos * X - sin * Y, sin * X + cos * Y);
}

Vector2F Vector2F::normalization()
{
	double length = Length_Vector2f();

	X /= length;
	Y /= length;

	return *this;
}




//operstor to simply print the object with cout 
std::ostream& operator<<(std::ostream& os, const Vector2F& v) {
	os << v.ToString();
	return os;
}

std::ostream& operator<<(std::ostream& os, const Vector3F& v)
{
	os << v.to_String();
	return os;
}
Vector3F::Vector3F(double X, double Y, double Z) :x(X), y(Y), z(Z) {}

double Vector3F::getX3D()const
{
	return x;
}
double Vector3F::getY3D()const
{
	return y;
}
double Vector3F::getZ3D()const
{
	return z;
}

void Vector3F::setX3D(double x)
{
	this->x = x;
}
void Vector3F::setY3D(double y)
{
	this->y = y;
}
void Vector3F::setZ3D(double z)
{
	this->z = z;
}

double Vector3F::Length_Vector3f()
{
	return  sqrt(x * x + y * y + z * z);
}

Vector3F Vector3F::normalize3d()
{
	double length = Length_Vector3f();

	x /= length;
	y /= length;
	z /= length;


	return *this;
}

double Vector3F::dotproduct(const Vector3F& r)
{
	return x * r.getX3D() + y * r.getY3D() + z * r.getZ3D();
}

Vector3F Vector3F::operator+(const Vector3F& other)
{
	return Vector3F(x + other.getX3D(), y + other.getY3D(), z + other.getZ3D());
}
Vector3F Vector3F::operator-(const Vector3F& other)
{
	return Vector3F(x - other.getX3D(), y - other.getY3D(), z - other.getZ3D());
}
Vector3F Vector3F::operator*(const Vector3F& other)
{
	return Vector3F(x * other.getX3D(), y * other.getY3D(), z * other.getZ3D());
}
Vector3F Vector3F::operator/(const Vector3F& other)
{
	return Vector3F(x / other.getX3D(), y / other.getY3D(), z / other.getZ3D());
}
Vector3F Vector3F::operator+(const double& other)
{
	return Vector3F(x + other, y + other, z + other);
}
Vector3F Vector3F::operator-(const double& other)
{
	return Vector3F(x - other, y - other, z - other);
}
Vector3F Vector3F::operator*(const double& other)
{
	return Vector3F(x * other, y * other, z * other);
}

Vector3F Vector3F::operator/(const double& other)
{
	return Vector3F(x / other, y / other, z / other);
}

Vector3F  Vector3F::crossproduct(Vector3F vector)
{
	double X_x = y * vector.getZ3D() - z * vector.getY3D();
	double Y_y = z * vector.getX3D() - x * vector.getZ3D();
	double Z_z = x * vector.getY3D() - y * vector.getX3D();


	return Vector3F(X_x, Y_y, Z_z);
}

std::string Vector3F::to_String() const
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}




//in my case it its getting the state of the key that was pressed or not 
bool Input::getKey(const int& keycode)
{
	if (glfwGetKey(Window::mywindow, keycode) == GLFW_PRESS)
	{
		return true;
	}

	return false;
}
//geting the state of mouse clicked 
bool Input::getMouseKey(const int& keycode)
{
	if (glfwGetMouseButton(Window::mywindow, keycode) == GLFW_PRESS)
	{
		return true;
	}

	return false;
}
/// <summary>
/// updates the lists where  i store the states of keys that was
/// pressed/released 
/// </summary>
void Input::update()
{
	FillStates(false, NUM_MOUSEKEYCODES, MousePressed, MouseReleased);
	FillStates(true, NUM_KEYCODES, pressedkeys, Releasedkeys);
	FillCurrents(true, NUM_KEYCODES, currentkeys);
	FillCurrents(false, NUM_MOUSEKEYCODES, CurrentMouseKeys);
}




/// <summary>
/// to get position of the mouse when it clicked 
/// </summary>
/// <returns></returns>
Vector2F Input::cursorPos()
{
	double xpos, ypos;
	glfwGetCursorPos(Window::mywindow, &xpos, &ypos);
	return Vector2F(xpos, ypos);
}

void Input::FillStates(bool iskeyboard, const int& allkeycode, std::list<int>& Pressedkey, std::list<int>& Releasedkeys)
{

	if (iskeyboard == false)
	{

		//released 
		Releasedkeys.clear();
		for (int i = 0; i < allkeycode; i++)
		{
			if (!getMouseKey(i) && UTils::Contains(CurrentMouseKeys, i))
			{
				Releasedkeys.emplace_back(i);
			}
		}


		//pressed
		Pressedkey.clear();
		for (int i = 0; i < allkeycode; i++)
		{
			if (getMouseKey(i) && !UTils::Contains(CurrentMouseKeys, i))
			{
				Pressedkey.emplace_back(i);
			}
		}

	}
	else if (iskeyboard == true)
	{
		//released

		Releasedkeys.clear();
		for (int i = 0; i < allkeycode; i++)
		{
			if (!getKey(i) && UTils::Contains(currentkeys, i))
			{
				Releasedkeys.emplace_back(i);
			}
		}
		//pressed

		Pressedkey.clear();
		for (int i = 0; i < allkeycode; i++)
		{
			if (getKey(i) && !UTils::Contains(currentkeys, i))
			{
				Pressedkey.emplace_back(i);
			}
		}
	}


}

void Input::FillCurrents(bool iskeyboard, const int& allkeycodes, std::list<int>& currents)
{
	if (iskeyboard == true)
	{
		currents.clear();
		for (int i = 0; i < allkeycodes; i++)
		{
			if (getKey(i))
			{
				currents.emplace_back(i);
			}
		}
	}
	else if (iskeyboard == false)
	{
		currents.clear();
		for (int i = 0; i < allkeycodes; i++)
		{
			if (getMouseKey(i))
			{
				currents.emplace_back(i);
			}
		}
	}
}

bool Input::GetStates(bool isMouse,bool ispressed, const int& keycodes)
{
	if (isMouse == true )
	{	//mouse
		if (ispressed == true) {
			if (UTils::Contains(MousePressed, keycodes) )
			{
				return true;
			}
			
		}
		else if (ispressed == false)
		{
			if (UTils::Contains(MouseReleased, keycodes))
			{
				return true;
			}
			
		}	
	}
	else
	{
		//keyboard
		if (ispressed == true) {
			if (UTils::Contains(pressedkeys, keycodes))
			{
				return true;
			}
			
		}
		else if (ispressed == false)
		{
			if (UTils::Contains(Releasedkeys, keycodes))
			{
				return true;
			}
			
		}

	}
	return false;



}

