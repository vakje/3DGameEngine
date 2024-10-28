#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
class Window
{
public:
	GLFWwindow* mywindow;
	Window();
	void SetWindow(int width, int height, const char* title);	
	~Window();
};
