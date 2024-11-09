#pragma once
#include "WindowComponent.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>
class Window;

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
    double dotproduct(Vector2F r);
    // returning vector it self after normalization(or making it equal to 1)
    Vector2F normalization();
    // functions for basic operations with vectors 
    //this is to add another vector 2f 
    Vector2F operator+(Vector2F other);
    Vector2F operator-(Vector2F other);
    Vector2F operator*(const Vector2F& other);
    Vector2F operator+(double num);
    Vector2F operator-(double num);
    Vector2F operator*(double num);

    Vector2F Rotate(double angle);
};
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

    double dotproduct(Vector3F r);
    Vector3F operator+(Vector3F other);
    Vector3F operator-(Vector3F other);
    Vector3F operator*(const Vector3F& other);
    Vector3F operator+(double num);
    Vector3F operator-(double num);
    Vector3F operator*(double num);

    Vector3F  crossproduct(Vector3F vector);

};


std::ostream& operator<<(std::ostream& os, const Vector2F& v);

 class Input 
{
   static std::list<int> currentkeys;
   static std::list<int> pressedkeys;
   static std::list<int> Releasedkeys;

   static std::list<int> CurrentMouseKeys;
   static std::list<int> MousePressed;
   static std::list<int> MouseReleased;

public:
  
    static bool getKey(const int& keycode);
    static bool getMouseKey(const int& keycode);
    static void update();
    static Vector2F cursorPos();
    static void FillStates(bool iskeyboardkey, const int& allkeycode, std::list<int>& keyboardkeys, std::list<int>& releasedkeyboardkeys);
    static void FillCurrents(bool iskeyboard, const int& allkeycodes, std::list<int>& currents);
    static bool GetStates(bool isMouse,bool ispressed ,const int& keycodes);
 
public:
    const static int NUM_KEYCODES = 256;
    const static int NUM_MOUSEKEYCODES = 5;


};