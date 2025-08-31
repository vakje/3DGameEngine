#include "Clock.h"

Time::Time()
{	
	//before loop time to make it in miliseconds
	m_Prevtime = std::chrono::high_resolution_clock::now();
}

float Time::getDeltaTime()
{
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> Deltatime = now - m_Prevtime;
	m_Prevtime = now;
	return Deltatime.count();
}





