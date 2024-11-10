#pragma once
#include "WindowComponent.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>
#include <type_traits>

template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
class Vector2F
{
    T X;
    T Y;

public:
    Vector2F(T x, T y) :X(x), Y(y) {}

    T get_X() const
    {
        return X;
    }
    T get_Y() const
    {
        return Y;
    }
    void set_X(T x)
    {
        this->X = x;
    }
    void set_Y(T y)
    {
        this->Y = y;
    }

    std::string ToString() const
    {
        return "(" + std::to_string(X) + "," + std::to_string(Y)  + ")" + "\n";
    }

    //returning the length of the vector or in another words hypotenus of the triangle 
    T Length_Vector2f()
    {
        return sqrt(X * X + Y * Y);
    }
    // overloading dot product for my vector2f c++ feature:)
    T dotproduct(const Vector2F& r)
    {
        return X * r.get_X() + Y * r.get_Y();
    }
    // returning vector it self after normalization(or making it equal to 1)
    Vector2F normalization()
    {
        T length = Length_Vector2f();

        X /= length;
        Y /= length;

        return *this;
    }
    static Vector2F cursorPos() {

        double xpos, ypos;
        glfwGetCursorPos(Window::mywindow, &xpos, &ypos);
        return Vector2F(xpos, ypos);

    }
    // functions for basic operations with vectors 
    //this is to add another vector 2f 
    Vector2F operator+(const Vector2F& other)
    {
        return Vector2F(X + other.get_X(), Y + other.get_Y());
    }
    Vector2F operator-(const Vector2F& other)
    {
        return Vector2F(X - other.get_X(), Y - other.get_Y());
    }
    Vector2F operator*(const Vector2F& other)
    {
        return Vector2F(X * other.get_X(), Y * other.get_Y());
    }
    Vector2F operator+(const T& num)
    {
        return Vector2F(X + num, Y + num);
    }
    Vector2F operator-(const T& num) 
    {
        return Vector2F(X - num, Y - num);
    }
    Vector2F operator*(const T& num) 
    {
        return Vector2F(X * num, Y * num);
    }

    Vector2F Rotate(const T& angle) 
    {
        T rad = angle * (3.14159265358 / 180);
        T sin = std::sin(rad);
        T cos = std::cos(rad);

        return Vector2F(cos * X - sin * Y, sin * X + cos * Y);
    }
};
template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Vector2F<T>& v) 
{
    os << v.ToString();
    return os;
}
template<Numeric T>
class Vector3F
{
    T x;
    T y;
    T z;
public:
    Vector3F(T X, T Y, T Z):x(X),y(Y),z(Z){}
    T getX3D()const 
    {
        return x;
    }
    T getY3D()const 
    {
        return y;
    }
    T getZ3D()const 
    {
        return z;
    }
    void setX3D(T x) 
    {
        this->x = x;
    }
    void setY3D(T y) 
    {
        this->y = y;
    }
    void setZ3D(T z) 
    {
        this->z = z;
    }
    T Length_Vector3f() 
    {
        return  sqrt(x * x + y * y + z * z);
    }
    Vector3F normalize3d() 
    {
        T length = Length_Vector3f();

        x /= length;
        y /= length;
        z /= length;


        return *this;
    }

    T dotproduct(const Vector3F& r) 
    {
        return x * r.getX3D() + y * r.getY3D() + z * r.getZ3D();
    }
    Vector3F operator+(const Vector3F& other)
    {
        return Vector3F(x + other.getX3D(), y + other.getY3D(), z + other.getZ3D());
    }
    Vector3F operator-(const Vector3F& other) 
    {
        return Vector3F(x - other.getX3D(), y - other.getY3D(), z - other.getZ3D());
    }
    Vector3F operator*(const Vector3F& other) 
    {
        return Vector3F(x * other.getX3D(), y * other.getY3D(), z * other.getZ3D());
    }
    Vector3F operator/(const Vector3F& other) 
    {
        return Vector3F(x / other.getX3D(), y / other.getY3D(), z / other.getZ3D());
    }
    Vector3F operator+(const T& other) 
    {
        return Vector3F(x + other, y + other, z + other);
    }
    Vector3F operator-(const T& other)
    {
        return Vector3F(x - other, y - other, z - other);
    }
    Vector3F operator*(const T& other)
    {
        return Vector3F(x * other, y * other, z * other);
    }
    Vector3F operator/(const T& other)
    {
        return Vector3F(x / other, y / other, z / other);
    }

    Vector3F  crossproduct(Vector3F vector) 
    {
        T X_x = y * vector.getZ3D() - z * vector.getY3D();
        T Y_y = z * vector.getX3D() - x * vector.getZ3D();
        T Z_z = x * vector.getY3D() - y * vector.getX3D();


        return Vector3F(X_x, Y_y, Z_z);
    }

    std::string to_String()const 
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")"+"\n";
    }

}; 
template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Vector3F<T>& v) 
{
    os << v.to_String();
    return os;
}