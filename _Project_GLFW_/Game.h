#pragma once
#include "InputSystem.h"
#include "Renderer.h"

struct Game 
{
	Renderer m_MyRenderer;
	
	void Initilize()
	{
		
		glEnable(GL_DEPTH_TEST);          // Enable depth testing
		glDepthFunc(GL_LESS);

		// Clear settings
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set clear color
		glClearDepth(1.0f);

		m_MyRenderer.InitilizeOpengl();
    }
	void Clear() 
	{
		m_MyRenderer.ClearScreen();

	}
	void MainCharacter() 
	{
		m_MyRenderer.Draw();
		InputHandlers();
	}
	void InputHandlers() 
	{
		
		
		Input::Update();
		if (Input::getStates(true, true, GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "we just pressed some mouse key at " << " " << Vector2F<int>::CursorPos() << " ";
		}
		if (Input::getStates(true, false, GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "we just released some mouse key" << std::endl;
		}
		if (Input::getStates(false, true, GLFW_KEY_ESCAPE))
		{
			std::cout << "Pressed Escape!" << std::endl;
			glfwSetWindowShouldClose(Window::m_mywindow, GLFW_TRUE);
		}
		
		
	
	}

};