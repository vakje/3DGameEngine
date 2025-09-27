#include "WindowComponent.h"



GLFWwindow* Window::m_mywindow;

Window::Window(int width, int height, const char* title)
{
	if (!glfwInit())
		return;

	m_mywindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_mywindow)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to init GLFW");
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(m_mywindow);
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("GLEW initialization failed!");
	}
}

Window::~Window() {
	if (m_mywindow) {
		glfwDestroyWindow(m_mywindow);
		glfwTerminate();
		m_mywindow = nullptr;
	}
}



