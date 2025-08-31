#pragma once
#include "WindowComponent.h"
#include "MathClasses.h" 
#include "Camera.h"
#include <filesystem>
#include <string>
#include <utility>
#include <fstream>
#include "Util.h"
#include <sstream>

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
	 unsigned int m_ShaderProgram,m_VAO,m_VBO,m_CBO,m_EBO;
	 //containers that has data about vertices and indices of an object (mesh)
	 std::vector<float> m_Vertices;
	 std::vector<unsigned int> m_Indices;
	 //camera instance for function calls from this class
	 Camera m_Cam;
	
public:	
	void ClearScreen();	
	void ObjectFileParser(const std::string& path, std::vector<float>& Vertices, std::vector<unsigned int>& Indices);
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

