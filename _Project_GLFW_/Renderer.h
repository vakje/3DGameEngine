#pragma once
#include "WindowComponent.h"
#include "MathClasses.h" 
#include "Camera.h"
#include <filesystem>
#include <string>
#include <utility>
#include <fstream>
#include "Util.h"
#include "Clock.h"
#include <sstream>
#include <charconv>
#include <string_view>
#include "SkyBox.h"
#include "Texture.h"
#include "../External/tinyloader/tiny_obj_loader.h"


struct Vertex {
	float px, py, pz;
	float u, v;
	
};

struct MaterialBatch
{
	int materialId;          // index into tinyobj::materials
	uint32_t indexOffset;    // start index in EBO
	uint32_t indexCount;     // number of indices to draws
};
class Renderer
{
	 //strings that represeting actual code of the file shader glcl
	 std::string m_VertexShaderSource;
	 std::string m_FragmentShaderSource;	
	 // Variables related to rendering:
     // ShaderProgram - controls how objects are Drawn (shaders)
     // VAO - stores the state needed to supply vertex data
     // VBO - stores vertex data (positions)
     // CBO - stores color data 
     // EBO - stores element/index data for indexed Drawing
	 unsigned int m_ShaderProgram, m_VAO, m_VBO, m_EBO, gSamplerLocation;
	 //containers that has data about vertices and indices of an object (meshes)
	 std::vector<Vertex> vertices;
	 std::vector<uint32_t> indices;
	 std::vector<tinyobj::material_t> materials;
	 std::vector<std::unique_ptr<Texture>> materialTextures;
	 std::vector<MaterialBatch> materialBatches;
	
	 //camera instance for function calls from this class
	 Camera m_Cam;
	 Time m_Time;
	 //textures
	 std::unique_ptr<Texture> tex;
	 SkyBox sky;
	 unsigned int m_SkyBoxVAO, m_SkyBoxVBO, m_skyShaderProgram, m_cubemapTexture;

public: 
	 //need for creating default constructor for renderer
	 Renderer() = default;
	 //preventing important copy and assignment operator copies from user side.
	 Renderer(const Renderer&) = delete;
	 Renderer& operator =(const Renderer&) = delete;
public:	
	void ClearScreen();	

	void LoadObjWithLib();

	void InitilizeOpengl();

	unsigned int CompileShaderFromSource(unsigned int shader_id, std::string& src);
	unsigned int CreateShaderFromStrings(std::string& VertexShader, std::string& fragmentshader);
	std::pair<std::string ,std::string> ReadFromShaderFile(const std::string& path);	
	
	void SetupMVP(unsigned int ShaderProgram);
	
	void setupSkyBoxMVP(unsigned int ShaderProgram);
	
	void Draw();
	
	~Renderer();
//tools
public:
	 std::string getVertex()const;
	 std::string getFragment()const;
	 
	 

};

