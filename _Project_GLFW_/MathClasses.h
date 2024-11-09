#pragma once
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>


class Vector2F
{
    double X;
    double Y;

public:
    Vector2F(double x, double y);

    double get_X() const;
    double get_Y() const;
    void set_X(double x);
    void set_Y(double y);

    std::string ToString() const;

    //returning the length of the vector or in another words hypotenus of the triangle 
    double Length_Vector2f();
    // overloading dot product for my vector2f c++ feature:)
    double dotproduct(const Vector2F& r);
    // returning vector it self after normalization(or making it equal to 1)
    Vector2F normalization();
    // functions for basic operations with vectors 
    //this is to add another vector 2f 
    Vector2F operator+(const Vector2F& other);
    Vector2F operator-(const Vector2F& other);
    Vector2F operator*(const Vector2F& other);
    Vector2F operator+(const double& num);
    Vector2F operator-(const double& num);
    Vector2F operator*(const double& num);

    Vector2F Rotate(const double& angle);
};
std::ostream& operator<<(std::ostream& os, const Vector2F& v);
class Vector3F
{
    double x;
    double y;
    double z;
public:
    Vector3F(double X, double Y, double z);
    double getX3D()const;
    double getY3D()const;
    double getZ3D()const;
    void setX3D(double x);
    void setY3D(double y);
    void setZ3D(double z);
    double Length_Vector3f();
    Vector3F normalize3d();

    double dotproduct(const Vector3F& r);
    Vector3F operator+(const Vector3F& other);
    Vector3F operator-(const Vector3F& other);
    Vector3F operator*(const Vector3F& other);
    Vector3F operator/(const Vector3F& other);
    Vector3F operator+(const double& num);
    Vector3F operator-(const double& num);
    Vector3F operator*(const double& num);
    Vector3F operator/(const double& num);

    Vector3F  crossproduct(Vector3F vector);

    std::string to_String()const;

}; 
std::ostream& operator<<(std::ostream& os, const Vector3F& v);