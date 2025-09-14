#pragma once

#include <chrono>
#include <iostream>
class Time
{   
    std::chrono::high_resolution_clock::time_point m_Prevtime;   
    
public:
    Time();
    float getDeltaTime();

   
};