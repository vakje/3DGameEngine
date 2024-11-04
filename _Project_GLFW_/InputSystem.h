#pragma once
#include "WindowComponent.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
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