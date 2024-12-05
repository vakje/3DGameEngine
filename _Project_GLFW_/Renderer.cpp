#include "Renderer.h"



void Renderer::ClearScreen()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::InitializeGraphics()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	std::filesystem::path fullpath = std::filesystem::current_path() / "TOOLS";
	std::string path = fullpath.string();

	GLFWimage images[1];

	//github dedac movtyan


	glfwSetWindowIcon(Window::mywindow, 1, images);

}

void Renderer::Initilize_opengl()
{
	//shaders  will be here also functions that connected with shaders 
	VertexShaderSource =
		"#version 330 core\n"
		"\n"
		"layout(location =0)in vec4 position;"
		"\n"
		"void main()\n"
		"{\n"
		"gl_Position = position;\n"
		"}\n";

	FragmentShaderSource =
		"#version 330 core\n"
		"\n"
		"layout(location =0) out vec4 color;"
		"\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0,0.0,0.0,1.0);\n"
		"}\n";

	ShaderProgram = CreateShaderFromStrings(VertexShaderSource, FragmentShaderSource);

	static const float g_vertex_buffer_data[] = {
	-0.25f, -0.25f, 0.0f,
	 0.25f, -0.25f, 0.0f,
	 0.0f,  0.25f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &VBO);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);



}

unsigned int Renderer::CompileShaderFromSource(unsigned int TYPE, std::string& src)
{
	unsigned int shader = glCreateShader(TYPE);
	const char* source = src.c_str();
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader Compilation Error: " << infoLog << std::endl;
	}

	return shader;
}

unsigned int Renderer::CreateShaderFromStrings(std::string& VertexShadersource, std::string& FragmentShadersource)
{
	unsigned int program = glCreateProgram();
	unsigned int VSS = CompileShaderFromSource(GL_VERTEX_SHADER, VertexShadersource);
	unsigned int FSS = CompileShaderFromSource(GL_FRAGMENT_SHADER, FragmentShadersource);

	glAttachShader(program, VSS);
	glAttachShader(program, FSS);
	glLinkProgram(program);
	glValidateProgram(program);

	int success;
	glGetShaderiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "Shader Creation Error: " << infoLog << std::endl;
	}

	glDeleteShader(VSS);
	glDeleteShader(FSS);

	return program;
}

void Renderer::drawTriangle()
{
	glUseProgram(ShaderProgram);

	// Bind VAO and draw the triangle
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glBindVertexArray(0);
}



std::string Renderer::get_vertex()const { return VertexShaderSource; }
std::string Renderer::get_fragment()const { return FragmentShaderSource; }






