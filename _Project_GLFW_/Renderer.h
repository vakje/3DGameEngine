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
	uint32_t indexCount;     // number of indices to draw
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
	 unsigned int m_ShaderProgram,m_VAO,m_VBO,m_EBO, gSamplerLocation,tex_VBO;
	 //containers that has data about vertices and indices of an object (meshes)
	 std::vector<Vertex> vertices;
	 std::vector<uint32_t> indices;
	 std::vector<tinyobj::material_t> materials;
	 std::vector<std::unique_ptr<Texture>> materialTextures;
	 std::vector<MaterialBatch> materialBatches;
	
	 //camera instance for function calls from this class
	 Camera m_Cam;
	 Time m_Time;
	 std::unique_ptr<Texture> tex;
	 
	
public:	
	void ClearScreen();	
	void Load_OBJ_withlib();
	void InitilizeOpengl();
	unsigned int CompileShaderFromSource(unsigned int shader_id, std::string& src);
	unsigned int CreateShaderFromStrings(std::string& VertexShader, std::string& fragmentshader);
	void SetupMVP(unsigned int ShaderProgram);
	void Draw();
	std::pair<std::string ,std::string> ReadFromShaderFile(const std::string& path);	
	~Renderer();
//tools
public:
	 std::string getVertex()const;
	 std::string getFragment()const;
	 
	 

};

