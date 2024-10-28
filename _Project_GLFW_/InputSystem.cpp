
#include "InputSystem.h"



Vector2F::Vector2F(float x, float y) : X(x), Y(y) {}

float Vector2F::get_X() const { return X; }
float Vector2F::get_Y() const { return Y; }
void Vector2F::set_X(float x) { X = x; }
void Vector2F::set_Y(float y) { Y = y; }

std::string Vector2F::ToString() const {
    return "(" + std::to_string(X) + "," + std::to_string(Y) + ")";
}

std::ostream& operator<<(std::ostream& os, const Vector2F& v) {
    os << v.ToString();
    return os;
}

