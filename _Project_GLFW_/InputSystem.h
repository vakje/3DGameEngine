#pragma once
#include "WindowComponent.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
class Window;
bool Contains(const std::list<int>& mylist, int num);
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

public:
  
    static bool getKey(int keycode);
    static void update();
    static bool getKeyPress(const int& keycode);
    static bool getKeyReleased(const int& keycode);
public:
    const static int NUM_KEYCODES = 256;


};