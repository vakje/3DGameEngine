#pragma once
#include "WindowComponent.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
class Window;

class Vector2F 
{
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
    static bool getKeyPress(const int& keycode);
    static bool getKeyReleased(const int& keycode);
    static bool getMousePress(const int& keycode);
    static bool getMouseReleased(const int& keycode);
    static Vector2F cursorPos();
 
public:
    const static int NUM_KEYCODES = 256;
    const static int NUM_MOUSEKEYCODES = 5;


};