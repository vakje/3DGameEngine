#include "Renderer.h"

std::filesystem::path fullpath = std::filesystem::current_path();

void Renderer::ClearScreen()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Renderer::SetWindowICON()
{
	//TODO icon 
	std::filesystem::path Toolspath = std::filesystem::current_path() / "TOOLS";
	std::string path = Toolspath.string();

	GLFWimage images[1];

	//github dedac movtyan


	glfwSetWindowIcon(Window::mywindow, 1, images);

}

void Renderer::Initilize_opengl()
{
	std::filesystem::path Toolspath = fullpath / "TOOLS\\M_Shaders.txt";
	std::string PATH = Toolspath.string();
	std::pair<std::string, std::string> Shaders;
	try {
		Shaders = ReadFromShaderFile(PATH);
	}
	catch (std::exception ex) { std::cout << " " << ex.what() << std::endl; }

	ShaderProgram = CreateShaderFromStrings(Shaders.first, Shaders.second);

	static const float g_color_buffer_data[] = {
		// Face 1 (Front - 2 triangles)
		1.0f, 0.0f, 0.0f,  // Bright Red
		0.9f, 0.1f, 0.0f,  // Darker Red
		0.8f, 0.2f, 0.0f,  // Orange-Red
		0.8f, 0.2f, 0.0f,  // Orange-Red
		0.7f, 0.3f, 0.0f,  // Orange
		1.0f, 0.0f, 0.0f,  // Bright Red

		// Face 2 (Back - 2 triangles)
		0.6f, 0.4f, 0.0f,  // Gold
		0.5f, 0.5f, 0.0f,  // Yellow
		0.4f, 0.6f, 0.2f,  // Yellow-Green
		0.4f, 0.6f, 0.2f,  // Yellow-Green
		0.3f, 0.7f, 0.3f,  // Light Green
		0.6f, 0.4f, 0.0f,  // Gold

		// Face 3 (Left - 2 triangles)
		0.2f, 0.8f, 0.4f,  // Greenish Teal
		0.1f, 0.9f, 0.5f,  // Aqua-Green
		0.0f, 1.0f, 0.6f,  // Aqua
		0.0f, 1.0f, 0.6f,  // Aqua
		0.2f, 0.8f, 0.4f,  // Greenish Teal
		0.1f, 0.9f, 0.5f,  // Aqua-Green

		// Face 4 (Right - 2 triangles)
		0.6f, 0.0f, 0.8f,  // Purple
		0.7f, 0.1f, 0.9f,  // Magenta
		0.8f, 0.2f, 1.0f,  // Violet
		0.8f, 0.2f, 1.0f,  // Violet
		0.6f, 0.0f, 0.8f,  // Purple
		0.7f, 0.1f, 0.9f,  // Magenta

		// Face 5 (Top - 2 triangles)
		1.0f, 0.8f, 0.0f,  // Light Orange
		1.0f, 0.6f, 0.2f,  // Peach
		0.9f, 0.4f, 0.4f,  // Pinkish
		0.9f, 0.4f, 0.4f,  // Pinkish
		1.0f, 0.8f, 0.0f,  // Light Orange
		1.0f, 0.6f, 0.2f,  // Peach

		// Face 6 (Bottom - 2 triangles)
		0.2f, 0.2f, 0.8f,  // Blue
		0.3f, 0.3f, 0.7f,  // Blue-Gray
		0.4f, 0.4f, 0.6f,  // Steel Blue
		0.4f, 0.4f, 0.6f,  // Steel Blue
		0.2f, 0.2f, 0.8f,  // Blue
		0.3f, 0.3f, 0.7f   // Blue-Gray
	};



	static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &VBO);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	 
	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);


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
	glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader Compilation Error (" << (TYPE == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "): " << infoLog << std::endl;
		glDeleteShader(shader); // Cleanup in case of failure.
		return 0; // Indicate failure with invalid ID.
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
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "Shader Creation Error: " << infoLog << std::endl;
	}

	glDeleteShader(VSS);
	glDeleteShader(FSS);

	return program;
}

void Renderer::draw()
{
	glUseProgram(ShaderProgram);
	Matrix<float> Instance(4,4,1.0f);
	
	Instance.SetupMVP(ShaderProgram);
	
	
	// Bind VAO and draw the triangle
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}

std::pair<std::string, std::string> Renderer::ReadFromShaderFile(const std::string& path)
{
	std::ifstream ifs(path);
	std::string line;
	std::stringstream ss[2];
	enum class shadertype
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	shadertype type = shadertype::NONE;
	if (!ifs.is_open())
	{
		throw std::runtime_error("Failed to open file: " + path);
	}
	while (std::getline(ifs, line))
	{

		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = shadertype::VERTEX;

			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = shadertype::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	if (ss[0].str().empty() || ss[1].str().empty()) {
		throw std::runtime_error("Incomplete shader file: " + path);
	}

	return { ss[0].str(),ss[1].str() };
}


Renderer::~Renderer()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);

}

std::string Renderer::get_vertex()const { return VertexShaderSource; }
std::string Renderer::get_fragment()const { return FragmentShaderSource; }

unsigned int Renderer::get_Shaderprogram() const
{
	return ShaderProgram;
}






