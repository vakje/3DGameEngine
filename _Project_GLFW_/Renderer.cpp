#include "Renderer.h"


void Renderer::ClearScreen()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::InitializeGraphics()
{
  glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
  //frontface will be draw clockwise
  glFrontFace(GL_CW);
  //get rid of the back face 
  glCullFace(GL_BACK);
  //to use only vixible faces 
  glEnable(GL_CULL_FACE);
  //it will know where in 3d space each pixel located (on the window)
  glEnable(GL_DEPTH_TEST);
  
  //to show exact color shading
  glEnable(GL_FRAMEBUFFER_SRGB);
}

void Renderer::SetWindowICON()
{
	//TODO icon 
	std::filesystem::path fullpath = std::filesystem::current_path()/"TOOLS";
	std::string path = fullpath.string();
	
	GLFWimage images[1];

	//github dedac movtyan
	

	glfwSetWindowIcon(Window::mywindow, 1, images);

}


