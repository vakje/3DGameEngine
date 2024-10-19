#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>


class Window
{
public:
	
	GLFWwindow* mywindow;
	Window() = default;
	void SetWindow(int width, int height, const char* title)
	{
		
		const int FramesPerSecond = 60;
		const int FrameDelay = 1000 / FramesPerSecond;
		
		uint32_t FrameStart;
		int frametime;

		if (!glfwInit())
			return;

		mywindow = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!mywindow)
		{
			glfwTerminate();
			return;
		}
		/* Make the window's context current */
		glfwMakeContextCurrent(mywindow);
		glfwSwapInterval(0);
		if (glewInit() != GLEW_OK) {
			std::cout << "GLEW initialization failed!" << std::endl;
			return;
		}
		int frames = 0;
		double lastTime = glfwGetTime()*1000;
		 
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(mywindow))
		{	
			
			    // putting seconds in milliseconds when i am multiplying
			    FrameStart = static_cast<uint32_t>(glfwGetTime() * 1000);
				/* Render here */				
				glClear(GL_COLOR_BUFFER_BIT);
				/* Swap front and back buffers */

				glfwSwapBuffers(mywindow);
				/* Poll for and process events */
				glfwPollEvents();

				frametime = static_cast<int>(glfwGetTime() * 1000) - FrameStart;

				// making sleep for make cap for frames
				if (FrameDelay > frametime) {
					std::this_thread::sleep_for(std::chrono::milliseconds(FrameDelay - frametime));
				}
				
				double currentTime = glfwGetTime() * 1000;
				frames++;
				
				if (currentTime - lastTime >= 1.0) // Print every second
				{
					std::cout << "FPS: " << frames << std::endl;
					frames = 0;
					lastTime = currentTime;
				}

		}

	}
	~Window() {
		glfwTerminate();
	}



};