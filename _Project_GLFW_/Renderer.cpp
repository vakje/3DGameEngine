#define TINYOBJLOADER_IMPLEMENTATION
#include "Renderer.h"

std::filesystem::path fullpath = std::filesystem::current_path();


void Renderer::ClearScreen()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::LoadObjWithLib()
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
		"TOOLS/models/niva.obj",
		"TOOLS/models/",
		true
	);

	if (!warn.empty()) std::cout << warn << std::endl;
	if (!err.empty())  std::cerr << err << std::endl;
	if (!ok) throw std::runtime_error("OBJ load failed");

	int currentMat = -1;
	uint32_t batchStart = 0;

	vertices.reserve(vertices.size());
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
	const auto shaderpath = (fullpath / "TOOLS" / "M_Shaders.shader").string();

	const auto skyboxshader = (fullpath / "TOOLS" / "skybox.shader").string();
	
	std::pair<std::string, std::string> Shaders;
	std::pair<std::string, std::string> sky_shaders;
	
	

	try {
		Shaders = ReadFromShaderFile(shaderpath);
		sky_shaders = ReadFromShaderFile(skyboxshader);
	}
	catch (std::exception& ex) { std::cout << " " << ex.what() << std::endl; }

	m_ShaderProgram = CreateShaderFromStrings(Shaders.first, Shaders.second);
	m_skyShaderProgram = CreateShaderFromStrings(sky_shaders.first, sky_shaders.second);
	auto start = std::chrono::high_resolution_clock::now();
	try {
		LoadObjWithLib();
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
	glGenVertexArrays(1, &m_SkyBoxVAO);
	glGenBuffers(1, &m_SkyBoxVBO);
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
			std::string texPath = "TOOLS/textures/" + mat.diffuse_texname;
			auto tex = std::make_unique<Texture>(
				GL_TEXTURE_2D,
				texPath
			);
			
			tex->load();
			materialTextures.push_back(std::move(tex));
		}
		else {
			materialTextures.push_back(nullptr);
		}

	}

	try
	{
		m_cubemapTexture = sky.loadCubemap();
	}
	catch (const std::runtime_error& ex) { std::cout << " " << ex.what() << "\n"; }

	
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
 
	angle += m_Cam.getSpeed() * m_Cam.getFov() * 2;//just for acceleration 
	
	if (angle >= 360) 
	{
		angle = 0;
	}
	
	I = M.Scale(I, forScale)  * M.Translate(I, forTranslation);
	//* M.Rotate(I, angle, forRotation)
	
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

void Renderer::setupSkyBoxMVP(unsigned int skyShaderProgram)
{
	
	Matrix<float> skyboxview = m_Cam.getLookat(m_Cam.getCameraPosition(), m_Cam.getCameraTarget(), m_Cam.getCameraUp());;
	Matrix<float> projection = m_Cam.getProjection(m_Cam.getFov(), m_Cam.getAspectRatio(), m_Cam.getNearPlane(), m_Cam.getFarPlane());
	skyboxview.RemoveTranslation(skyboxview);

	std::vector<GLfloat> glvector;
	unsigned int SViewLocation = glGetUniformLocation(skyShaderProgram, "view");
	glvector.clear();
	for (size_t col = 0; col < 4; ++col) {
		for (size_t row = 0; row < 4; ++row) {
			glvector.push_back(skyboxview(row, col)); 
		}
	}
	glUniformMatrix4fv(SViewLocation, 1, false, glvector.data());


	unsigned int SProjectionLocation = glGetUniformLocation(skyShaderProgram, "projection");
	glvector.clear();
	for (size_t col = 0; col < 4; ++col) {
		for (size_t row = 0; row < 4; ++row) {
			glvector.push_back(projection(row, col));  
		}
	}
	glUniformMatrix4fv(SProjectionLocation, 1, false, glvector.data());

	
}

void Renderer::Draw()
{
	glDepthFunc(GL_LEQUAL);

	glUseProgram(m_skyShaderProgram);

	setupSkyBoxMVP(m_skyShaderProgram);

	glBindVertexArray(m_SkyBoxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_SkyBoxVBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		sky.m_SkyBoxVertices.size() * sizeof(float),
		sky.m_SkyBoxVertices.data(),
		GL_STATIC_DRAW
	);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		nullptr
	);

	glEnableVertexAttribArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthFunc(GL_LESS);
	
	
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
	glDeleteVertexArrays(1, &m_SkyBoxVAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_SkyBoxVBO);
}

std::string Renderer::getVertex()const { return m_VertexShaderSource; }
std::string Renderer::getFragment()const { return m_FragmentShaderSource; }










