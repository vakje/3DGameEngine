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

	 


	glfwSetWindowIcon(Window::mywindow, 1, images);

}

void Renderer::objfileparser(const std::string& path, std::vector<float>& Vertices, std::vector<unsigned int>& Indices)
{
		//this line makes full path of the file must be like ..root\\user\\tools\\file.obj
		std::filesystem::path Toolspath = std::filesystem::current_path() / "TOOLS" / path;
		// this must take and transform that in string
		std::string PATH = Toolspath.string();
		//this must split the string and take last file
		std::string splitedtoken = UTils::FileChecker(PATH, "\\");
		std::cout << "this is the final splited thing:  " << splitedtoken << "  " << std::endl;
		if (!splitedtoken.find(".obj"))
		{
			std::cout << "this is not a obj file" << std::endl;
		}
		std::ifstream file(PATH);

		if (!file.is_open())
		{
			std::cout << "file not found" << std::endl;
		}

		std::string line;
		std::string v;
		std::string i;
		std::vector<std::string> StringV;
		std::vector<std::string> StringI;
		std::getline(file, line);


		while (std::getline(file, line))
		{

			if (line[0] == 'v')
			{


				//somehow in this chunck of code Indices are puted into the vector not vertices		
				StringV = UTils::splitString(line, " ");

				// transfer this data to original Indices vector
				//also parsing it to float 
				for (auto& V : StringV)
				{
					try {
						
						Vertices.push_back(std::stof(V));
					}
					catch (std::exception ex)
					{
						//really nothing i need to do with it... its complaining about some characters in the beginning of vertices data
					}
				}


			}if (line[0] == 'f')
			{
				//somehow in this chunck of code vertices are puted into the vector not indices
				StringI = UTils::splitString(line, " ");

				// transfer this data to original vertex vector
				//also parsing it to float 
				for (auto& Index : StringI)
				{
					try {
						
						Indices.push_back(std::stoul(Index) - 1);
					}
					catch (std::exception ex)
					{
						//really nothing i need to do with it... its complaining about some characters  in the beginning of vertices data
					}
				}


			}
		}
		file.close();
	
}

void Renderer::Initilize_opengl()
{
	std::filesystem::path Toolspath = fullpath / "TOOLS\\M_Shaders.txt";
	std::string ShaderPATH = Toolspath.string();
	std::pair<std::string, std::string> Shaders;
	try {
		Shaders = ReadFromShaderFile(ShaderPATH);
	}
	catch (std::exception ex) { std::cout << " " << ex.what() << std::endl; }

	ShaderProgram = CreateShaderFromStrings(Shaders.first, Shaders.second);
	
	std::string ObjPATH = "Cube.obj";
	
	
	objfileparser(ObjPATH, Vertices, Indices);

	
	float time = glfwGetTime();
	int Vertices_size = Vertices.size();
	float* colors = new float[Vertices_size];
	for (int i = 0; i < Vertices_size; i++)
	{
		colors[i] = 0.5f * (sin(time + i * 0.9f) + 1.0f);
	}
	//now giving this data to our GPU
   // Generate  buffers, put the resulting identifier in vertexbuffer|| indexbuffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	
	glBufferData(GL_ARRAY_BUFFER, Vertices_size * sizeof(float), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	// Unbind VAO 
	glBindVertexArray(0);
	delete[] colors;

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
	//this Class must instantiated to access it's core functions
	Matrix<float> Instance(4, 4, 1.0f);

	Instance.SetupMVP(ShaderProgram);


	// Bind VAO and draw the triangle
	glBindVertexArray(VAO);
	
	
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_LINES, Indices.size(), GL_UNSIGNED_INT, 0);

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










