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
	// Change from 3.3 to 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Make the window's context current */
	glfwMakeContextCurrent(m_mywindow);
	glfwSwapInterval(0);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::exception("Failed to initialize GLAD");
	}
}

Window::~Window() {
	if (m_mywindow) {
		glfwDestroyWindow(m_mywindow);
		glfwTerminate();
		m_mywindow = nullptr;
	}
}



