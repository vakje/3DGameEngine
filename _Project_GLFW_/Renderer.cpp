#define TINYOBJLOADER_IMPLEMENTATION
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
//AI optimized my stupid version of obj file parser will have it here like idle  
void Renderer::OtimizedObjectFileParser(const std::string& path, std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	// Read whole file at once
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::cerr << "File not found: " << path << "\n";
		return;
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	std::string buffer(size, '\0');
	if (!file.read(buffer.data(), size)) {
		std::cerr << "Failed to read file\n";
		return;
	}

	// Reserve vectors to avoid reallocations
	vertices.reserve(1000000); // adjust based on expected model
	indices.reserve(1000000);

	std::string_view view(buffer);
	size_t line_start = 0;

	while (line_start < view.size()) {
		size_t line_end = view.find('\n', line_start);
		if (line_end == std::string_view::npos)
			line_end = view.size();

		std::string_view line = view.substr(line_start, line_end - line_start);
		line_start = line_end + 1;

		if (line.empty() || line[0] == '#') continue; // skip empty or comment

		if (line[0] == 'v' && (line.size() > 1 && line[1] == ' ')) {
			// Vertex line
			line.remove_prefix(2); // skip "v "
			while (!line.empty()) {
				// Skip whitespace
				size_t start = line.find_first_not_of(" \t\r");
				if (start == std::string_view::npos) break;
				line.remove_prefix(start);

				size_t end = line.find_first_of(" \t\r");
				std::string_view token = line.substr(0, end);
				line.remove_prefix(token.size());

				float value;
				auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);
				if (ec == std::errc()) {
					vertices.push_back(value);
				}
			}
		}
		else if (line[0] == 'f' && (line.size() > 1 && line[1] == ' ')) {
			// Face line
			line.remove_prefix(2); // skip "f "
			while (!line.empty()) {
				size_t start = line.find_first_not_of(" \t\r");
				if (start == std::string_view::npos) break;
				line.remove_prefix(start);

				size_t end = line.find_first_of(" \t\r");
				std::string_view token = line.substr(0, end);
				line.remove_prefix(token.size());

				// Handle possible slashes (v/vt/vn)
				size_t slash_pos = token.find('/');
				if (slash_pos != std::string_view::npos)
					token.remove_suffix(token.size() - slash_pos);

				unsigned int idx;
				auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), idx);
				if (ec == std::errc()) {
					indices.push_back(idx - 1); // OBJ indices are 1-based
				}
			}
		}
	}
}

void Renderer::Load_OBJ_withlib()
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	

	std::string warn, err;

	bool ok = tinyobj::LoadObj(
		&attrib,
		&shapes,
		&materials,
		&warn,
		&err,
		"TOOLS/cubeTextured.obj",
		"TOOLS/",
		true
	);

	if (!warn.empty()) std::cout << warn << std::endl;
	if (!err.empty())  std::cerr << err << std::endl;
	if (!ok) throw std::runtime_error("OBJ load failed");

	int currentMat = -1;
	uint32_t batchStart = 0;
	for (const auto& shape : shapes) {
		size_t index_offset = 0;

		for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
			int fv = shape.mesh.num_face_vertices[f];
			int matId = shape.mesh.material_ids[f];
			// start new batch if material changed
			if (matId != currentMat)
			{
				if (currentMat != -1)
				{
					materialBatches.push_back({
						currentMat,
						batchStart,
						uint32_t(indices.size() - batchStart)
						});
				}

				currentMat = matId;
				batchStart = indices.size();
			}
			for (int v = 0; v < fv; v++) {
				tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

				Vertex vert{};

				vert.px = attrib.vertices[3 * idx.vertex_index + 0];
				vert.py = attrib.vertices[3 * idx.vertex_index + 1];
				vert.pz = attrib.vertices[3 * idx.vertex_index + 2];

				if (idx.texcoord_index >= 0) {
					vert.u = attrib.texcoords[2 * idx.texcoord_index + 0];
					vert.v = 1.0f - attrib.texcoords[2 * idx.texcoord_index + 1];
				}

				vertices.push_back(vert);
				indices.push_back(indices.size());
			}

			index_offset += fv;
		}
	}
	// push last batch
	if (currentMat != -1)
	{
		materialBatches.push_back({
			currentMat,
			batchStart,
			uint32_t(indices.size() - batchStart)
			});
	}


	
}

void Renderer::InitilizeOpengl()
{
	std::filesystem::path Shaderspath = fullpath / "TOOLS" / "M_Shaders.shader";
	std::string ShaderPATH = Shaderspath.string();
	std::pair<std::string, std::string> Shaders;
	try {
		Shaders = ReadFromShaderFile(ShaderPATH);
	}
	catch (std::exception ex) { std::cout << " " << ex.what() << std::endl; }

	m_ShaderProgram = CreateShaderFromStrings(Shaders.first, Shaders.second);
	
	std::string ObjPATH = "cube.obj";
	auto start = std::chrono::high_resolution_clock::now();
	try {
		Load_OBJ_withlib();
		if (vertices.empty() || indices.empty())
			throw std::runtime_error("OBJ file did not load vertices or indices correctly");

		for (size_t i = 0; i < indices.size(); ++i) {
			if (indices[i] >= vertices.size()) {
				throw std::runtime_error("Index out of range");
			}
		}
	}
	catch (std::exception& ex) {
		std::cout << " " << ex.what() << std::endl;
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration<double>(end - start).count() << " seconds\n";

	//now giving this data to our GPU
    // Generate  buffers, put the resulting identifier in vertexbuffer|| indexbuffer
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	
	
	
	glBindVertexArray(m_VAO);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, px));
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));
	glEnableVertexAttribArray(1);
	
	
	// Unbind VAO 
	glBindVertexArray(0);

	materialTextures.reserve(materials.size());
	for (auto& mat : materials) {
		if (!mat.diffuse_texname.empty()) {
			
			auto tex = std::make_unique<Texture>(
				GL_TEXTURE_2D,
				("TOOLS/" + mat.diffuse_texname).c_str()
			);
			
			tex->load();
			materialTextures.push_back(std::move(tex));
		}
		else {
			materialTextures.push_back(nullptr);
		}

	}
	
	
	

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
	
	I = M.Scale(I, forScale)  * M.Translate(I, forTranslation);
	//* M.Rotate(I, angle,forRotation)
	
	m_Cam.InputValidation(m_Deltatime);
	m_Cam.MouseMovement();
	//view matrix creation
	Matrix<float> view = m_Cam.getLookat(m_Cam.getCameraPosition(), m_Cam.getCameraTarget(), m_Cam.getCameraUp());
	
	
   
	//projection matrix calculating
	Matrix<float> projection = m_Cam.getProjection(m_Cam.getFov(), m_Cam.getAspectRatio(), m_Cam.getNearPlane(), m_Cam.getFarPlane());

	
	//making projection formula mvp = projection * view * model;
	Matrix<float> mvp = projection * view * I;

	//mvp matrix realization 
	unsigned int mvplocation = glGetUniformLocation(ShaderProgram, "u_MVP");
	if(mvplocation ==-1)
	{
		std::cerr << "Error getting uniform location of mvp\n";
	}
	std::vector<GLfloat> glvector;
	for (size_t col = 0; col < 4; ++col) {
		for (size_t row = 0; row < 4; ++row) {
			glvector.push_back(mvp(row, col)); // Column-major order needed for opengl 
		}
	}
	
	glUniformMatrix4fv(mvplocation, 1, false, glvector.data());

	gSamplerLocation = glGetUniformLocation(ShaderProgram, "gSampler");
	if(gSamplerLocation == -1)
	{
		std::cout << "Error getting uniform location of gSampler\n";
	}


}

void Renderer::Draw()
{
	glUseProgram(m_ShaderProgram);
	//function that setups projection and calculations for objects to rotate
	SetupMVP(m_ShaderProgram);
	
	// Bind VAO and draw the triangle
	glBindVertexArray(m_VAO);
	
	
	for (const auto& batch : materialBatches)
	{
		if (materialTextures[batch.materialId])
		{
			materialTextures[batch.materialId]->bind(GL_TEXTURE0);
		}

		glUniform1i(gSamplerLocation, 0);

		glDrawElements(
			GL_TRIANGLES,
			batch.indexCount,
			GL_UNSIGNED_INT,
			(void*)(batch.indexOffset * sizeof(uint32_t))
		);
	}
	

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
	glDeleteBuffers(1, &tex_VBO);
	 
	
}

std::string Renderer::getVertex()const { return m_VertexShaderSource; }
std::string Renderer::getFragment()const { return m_FragmentShaderSource; }










