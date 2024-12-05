#pragma once
#include "WindowComponent.h"
#include <filesystem>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>



class Renderer
{
	 std::string VertexShaderSource;
	 std::string FragmentShaderSource;
	 unsigned int ShaderProgram,VAO,VBO,CBO;
	 //ShaderProgram actual shaders that are compiled are stored in here
	 //VAO vertex atribute
	 //vertex buffer
	 // color buffer
public:
	
	void ClearScreen();
	void InitializeGraphics();
	void SetWindowICON();
	void Initilize_opengl();
	unsigned int CompileShaderFromSource(unsigned int shader_id, std::string& src);
	unsigned int CreateShaderFromStrings(std::string& VertexShader, std::string& fragmentshader);
	void drawTriangle();
	std::pair<std::string ,std::string> ReadFromShaderFile(const std::string& path);

public:
	 std::string get_vertex()const;
	 std::string get_fragment()const;

};

