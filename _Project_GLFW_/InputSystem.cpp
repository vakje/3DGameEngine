
#include "InputSystem.h"

std::list<int> Input::currentkeys;
std::list<int> Input::pressedkeys;
std::list<int> Input::Releasedkeys;



Vector2F::Vector2F(float x, float y) : X(x), Y(y) {}

float Vector2F::get_X() const { return X; }
float Vector2F::get_Y() const { return Y; }
void Vector2F::set_X(float x) { X = x; }
void Vector2F::set_Y(float y) { Y = y; }

std::string Vector2F::ToString() const {
    return "(" + std::to_string(X) + "," + std::to_string(Y) + ")";
}

bool Contains(const std::list<int>& mylist, int num)
{
    return std::find(mylist.begin(), mylist.end(), num) != mylist.end();
}

std::ostream& operator<<(std::ostream& os, const Vector2F& v) {
    os << v.ToString();
    return os;
}




bool Input::getKey(int keycode)
{
    if (glfwGetKey(Window::mywindow, keycode) == GLFW_PRESS ) 
    {
        return true;
    }

    return false;
}

void Input::update()
{
    Releasedkeys.clear();
    for (int i = 0; i < NUM_KEYCODES; i++)
    {
        if (!getKey(i) && Contains(currentkeys, i))
        {
            Releasedkeys.emplace_back(i);
        }
    }

    pressedkeys.clear();
    for (int i = 0; i < NUM_KEYCODES; i++)
    {
        if (getKey(i) && !Contains(currentkeys,i))
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
}

bool Input::getKeyPress(const int& keycode)
{
    if (Contains(pressedkeys, keycode)) 
    {
        return true;
    }
    
    return false;
}

bool Input::getKeyReleased(const int&  keycode)
{
    if (Contains(Releasedkeys, keycode))
    {
        return true;
    }

    return false;
}
