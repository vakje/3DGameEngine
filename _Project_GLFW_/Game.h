#pragma once
#include "InputSystem.h"
#include "Renderer.h"

struct Game 
{
	Renderer MyRenderer;
	
	void Initilize()
	{
		
		glEnable(GL_DEPTH_TEST);          // Enable depth testing
		glDepthFunc(GL_LESS);

		// Clear settings
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set clear color
		glClearDepth(1.0f);

		MyRenderer.Initilize_opengl();
    }
	void Clear() 
	{
		MyRenderer.ClearScreen();

	}
	void MainCharacter() 
	{
		MyRenderer.draw();
		InputHandlers();
	}
	void InputHandlers() 
	{
		
		
		Input::update();
		if (Input::GetStates(true, true, GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "we just pressed some mouse key at " << " " << Vector2F<int>::cursorPos() << " ";
		}
		if (Input::GetStates(true, false, GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "we just released some mouse key" << std::endl;
		}if (Input::GetStates(false, true, GLFW_KEY_ESCAPE))
		{
			std::cout << "Pressed Escape!" << std::endl;
			glfwSetWindowShouldClose(Window::mywindow, GLFW_TRUE);
		}
		
		
	
	}

};