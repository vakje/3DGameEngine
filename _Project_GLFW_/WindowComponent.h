#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>



class Window
{
	
public:
	static GLFWwindow* m_mywindow;	
	Window(int width, int height, const char* title);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};
