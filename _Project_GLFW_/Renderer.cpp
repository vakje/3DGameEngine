#include "Renderer.h"

std::filesystem::path fullpath = std::filesystem::current_path();

void Renderer::ClearScreen()
{	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ObjectFileParser(const std::string& path, std::vector<float>& Vertices, std::vector<unsigned int>& Indices)
{
		//this line makes full path of the file must be like ..root\\user\\tools\\file.obj
		std::filesystem::path Toolspath = std::filesystem::current_path() / "TOOLS" / path;
		// this must take and transform that in string
		std::string PATH = Toolspath.string();
		//this must split the string and take last file
		std::string lastfile = UTils::SplitPath(PATH);
		std::cout << "Meshe's Name:  " << lastfile << "  " << std::endl;
		if (lastfile.find(".obj") == std::string::npos)
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
			// 'v' lines contain vertex positions
			if (line[0] == 'v')
			{


				//somehow in this chunck of code Indices are puted into the vector not vertices		
				StringV = UTils::SplitString(line, " ");

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

			 // 'f' lines contain face indices
			}if (line[0] == 'f')
			{
				
				StringI = UTils::SplitString(line, " ");

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

void Renderer::InitilizeOpengl()
{
	std::filesystem::path Toolspath = fullpath / "TOOLS" / "M_Shaders.txt";
	std::string ShaderPATH = Toolspath.string();
	std::pair<std::string, std::string> Shaders;
	try {
		Shaders = ReadFromShaderFile(ShaderPATH);
	}
	catch (std::exception ex) { std::cout << " " << ex.what() << std::endl; }

	m_ShaderProgram = CreateShaderFromStrings(Shaders.first, Shaders.second);
	
	std::string ObjPATH = "cube.obj";
	
	
	ObjectFileParser(ObjPATH, m_Vertices, m_Indices);

	
	float m_time = glfwGetTime();
	int Vertices_size = m_Vertices.size();
	float* colors = new float[Vertices_size];
	for (int i = 0; i < Vertices_size; i++)
	{
		colors[i] = 0.5f * (cos(m_time + i * 0.9f) + 1.0f);
	}
	//now giving this data to our GPU
    // Generate  buffers, put the resulting identifier in vertexbuffer|| indexbuffer
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	
	glBindVertexArray(m_VAO);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	glGenBuffers(1, &m_CBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
	
	glBufferData(GL_ARRAY_BUFFER, Vertices_size * sizeof(float), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	
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
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
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

double angle = 0.0;

void Renderer::SetupMVP(unsigned int ShaderProgram)
{
	Vector3F<float> forTranslation(1.0f, 0.0f, 0.0f);
	Vector3F<float> forRotation(0.0f, 1.0f, 0.0f);
	Vector3F<float> forScale(1.0f, 1.0f, 1.0f);
	
	Matrix<float> I(4, 4, 1.0f);
	I.Initidentity(4);
	
	float m_Deltatime = m_Time.getDeltaTime();
	Matrix<float> M(4, 4, 1.0f);
 
	angle += m_Cam.getSpeed() * m_Cam.getFov() * 2;
	
	if (angle >= 360) 
	{
		angle = 0;
	}
	
	I = M.Scale(I, forScale) * M.Rotate(I, angle,forRotation) * M.Translate(I, forTranslation);

	
	m_Cam.InputValidation(m_Deltatime);
	//m_Cam.MouseMovement();
	//view matrix creation
	Matrix<float> view = m_Cam.getLookat(m_Cam.getCameraPosition(), m_Cam.getCameraTarget(), m_Cam.getCameraUp());
	
	
   
	//projection matrix calculating
	Matrix<float> projection = m_Cam.getProjection(m_Cam.getFov(), m_Cam.getAspectRatio(), m_Cam.getNearPlane(), m_Cam.getFarPlane());

	
	//making projection formula mvp = projection * view * model;
	Matrix<float> mvp = projection * view * I;

	//mvp matrix realization 
	unsigned int mvplocation = glGetUniformLocation(ShaderProgram, "u_MVP");
	
	std::vector<GLfloat> glvector;
	for (size_t col = 0; col < 4; ++col) {
		for (size_t row = 0; row < 4; ++row) {
			glvector.push_back(mvp(row, col)); // Column-major order needed for opengl 
		}
	}
	
	glUniformMatrix4fv(mvplocation, 1, false, glvector.data());
}

void Renderer::Draw()
{
	glUseProgram(m_ShaderProgram);
	//function that setups projection and calculations for objects to rotate
	SetupMVP(m_ShaderProgram);

	// Bind VAO and draw the triangle
	glBindVertexArray(m_VAO);
	
	
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	

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
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_CBO);
}

std::string Renderer::getVertex()const { return m_VertexShaderSource; }
std::string Renderer::getFragment()const { return m_FragmentShaderSource; }










