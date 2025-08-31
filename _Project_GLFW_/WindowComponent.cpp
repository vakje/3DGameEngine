#include "WindowComponent.h"
#include "Game.h"
#include "Clock.h"

GLFWwindow* Window::m_mywindow;

Game game;

void Window::SetWindow(int width, int height, const char* title)
{
	if (!glfwInit())
		return;

	m_mywindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_mywindow)
	{
		glfwTerminate();
		return;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(m_mywindow);
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialization failed!" << std::endl;
		return;
	}
	int frames = 0;
	//before loop time to make it in miliseconds
	double lastTime = glfwGetTime() * 1000.0;
	
	Time time;
	
	game.Initilize();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_mywindow))
	{		
		/* Render here */		
		game.Clear();
		/* Swap front and back buffers */
		game.MainCharacter();     
		glfwSwapBuffers(m_mywindow);
		/* Poll for and process events */
		glfwPollEvents();
		//currenttime in the loop
		double currentTime = glfwGetTime() * 1000.0;
		//adding frames 
		frames++;
		//if the time in the loop - time before loop  is more than 1 miliseconds
		if (currentTime - lastTime >= 1000.0) // Print every second
		{
			//print out fps 
			std::cout << "FPS: " << frames << std::endl;
			//assigne to 0 to make it default again
			frames = 0;
			// and assingn to the timer before loop to update the value 
			lastTime = currentTime;
		}
		
	}

}
Window::~Window() {
	glfwDestroyWindow(m_mywindow);
	glfwTerminate();
}



