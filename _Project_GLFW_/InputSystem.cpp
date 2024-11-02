
#include "InputSystem.h"
#include "Util.h"

/// <summary>
/// declaring it before using cause they are static c++ feature:)
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
Vector2F::Vector2F(float x, float y) : X(x), Y(y) {}

float Vector2F::get_X() const { return X; }
float Vector2F::get_Y() const { return Y; }
void Vector2F::set_X(float x) { X = x; }
void Vector2F::set_Y(float y) { Y = y; }
/// <summary>
/// to string which informating the user 
/// </summary>
/// <returns></returns>
std::string Vector2F::ToString() const {
    return "(" + std::to_string(X) + "," + std::to_string(Y) + ")";
}


//operstor to simply print the object with cout 
std::ostream& operator<<(std::ostream& os, const Vector2F& v) {
    os << v.ToString();
    return os;
}



//in my case it its getting the state of the key that was pressed or not 
bool Input::getKey(const int& keycode)
{
    if (glfwGetKey(Window::mywindow, keycode) == GLFW_PRESS ) 
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
/// used. 
/// </summary>
void Input::update()
{
    MouseReleased.clear();
    for (int i = 0; i < NUM_MOUSEKEYCODES; i++)
    {
        if (!getMouseKey(i) && UTils::Contains(CurrentMouseKeys, i))
        {
            MouseReleased.emplace_back(i);
        }
    }
   
    MousePressed.clear();
    for (int i = 0; i < NUM_MOUSEKEYCODES; i++)
    {
        if (getMouseKey(i) && !UTils::Contains(CurrentMouseKeys, i))
        {
            MousePressed.emplace_back(i);
        }
    }

    Releasedkeys.clear();
    for (int i = 0; i < NUM_KEYCODES; i++)
    {
        if (!getKey(i) && UTils::Contains(currentkeys, i))
        {
            Releasedkeys.emplace_back(i);
        }
    }

    pressedkeys.clear();
    for (int i = 0; i < NUM_KEYCODES; i++)
    {
        if (getKey(i) && !UTils::Contains(currentkeys,i))
        {
            pressedkeys.emplace_back(i);
        }
    }
    currentkeys.clear();

    for (int i = 0; i < NUM_KEYCODES; i++)
    {
        if (getKey(i)) 
        {
            currentkeys.emplace_back(i);
        }
    }
    CurrentMouseKeys.clear();
    for (int i = 0; i < NUM_MOUSEKEYCODES; i++)
    {
        if (getMouseKey(i))
        {
            CurrentMouseKeys.emplace_back(i);
        }
    }
}

bool Input::getKeyPress(const int& keycode)
{
    if (UTils::Contains(pressedkeys, keycode))
    {
        return true;
    }
    
    return false;
}

bool Input::getKeyReleased(const int&  keycode)
{
    if (UTils::Contains(Releasedkeys, keycode))
    {
        return true;
    }

    return false;
}

bool Input::getMousePress(const int& keycode)
{
    if (UTils::Contains(MousePressed, keycode))
    {
        return true;
    }

    return false;
}

bool Input::getMouseReleased(const int& keycode)
{
    if (UTils::Contains(MouseReleased, keycode))
    {
        return true;
    }

    return false;
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


