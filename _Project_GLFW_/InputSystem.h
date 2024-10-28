#pragma once
#include <string>
#include <iostream>


class Vector2F {
    float X;
    float Y;

public:
    Vector2F(float x, float y);

    float get_X() const;
    float get_Y() const;
    void set_X(float x);
    void set_Y(float y);

    std::string ToString() const;
};

// Non-member operator<< function
std::ostream& operator<<(std::ostream& os, const Vector2F& v);
