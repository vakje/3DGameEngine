#include <iostream>
#include "WindowComponent.h"
#include "Game.h"

const int WIDTH = 2560;
const int HEIGHT = 1440;
const char* TITLE = "3D GAME ENGINE";

Game game;
int main()
{
	try {
		Window win(WIDTH, HEIGHT, TITLE);
		int frames = 0;

		double lastTime = glfwGetTime() * 1000.0;
		game.Initilize();
		const double FrameDelay = 1000.0 / 75;//making framedelay 
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(Window::m_mywindow))
		{

			/* Render here */
			game.Clear();
			/* Swap front and back buffers */
			game.MainCharacter();
			glfwSwapBuffers(Window::m_mywindow);
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
	}catch(std::exception& ex)
	{
		std::cerr << "Fatal error occured:" << ex.what() << "\n";
	}

	std::cout << "-----------------------------------------------\n" << std::flush;
     
}