#pragma once
#include "WindowComponent.h"
#include "MathClasses.h" 
#include <filesystem>
#include <string>
#include <utility>
#include <fstream>
#include "Util.h"
#include <sstream>

class Renderer
{
	 std::string VertexShaderSource;
	 std::string FragmentShaderSource;
	 //ShaderProgram actual shaders that are compiled are stored in here
	 //VAO vertex atribute
	 //vertex buffer
	 // color buffer
	 unsigned int ShaderProgram,VAO,VBO,CBO,EBO;	 
	 std::vector<float> Vertices;
	 std::vector<unsigned int> Indices;
	
	
public:
	
	void ClearScreen();	
	void SetWindowICON();
	void objfileparser(const std::string& path, std::vector<float>& Vertices, std::vector<unsigned int>& Indices);
	
	void Initilize_opengl();
	unsigned int CompileShaderFromSource(unsigned int shader_id, std::string& src);
	unsigned int CreateShaderFromStrings(std::string& VertexShader, std::string& fragmentshader);
	void draw();
	std::pair<std::string ,std::string> ReadFromShaderFile(const std::string& path);	
	~Renderer();
//tools
public:
	 std::string get_vertex()const;
	 std::string get_fragment()const;
	
	 

};

