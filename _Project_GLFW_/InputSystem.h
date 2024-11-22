#pragma once
#include "WindowComponent.h"
#include "MathClasses.h"
class Window;




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
   
    static void FillStates(bool iskeyboardkey, const int& allkeycode, std::list<int>& keyboardkeys, std::list<int>& releasedkeyboardkeys);
    static void FillCurrents(bool iskeyboard, const int& allkeycodes, std::list<int>& currents);
    static bool GetStates(bool isMouse,bool ispressed ,const int& keycodes);
 
public:
    const static int NUM_KEYCODES = 348;
    const static int NUM_MOUSEKEYCODES = 5;


};