#pragma once
#include "WindowComponent.h"
#include <filesystem>
#include <string>



class Renderer
{
	 std::string VertexShaderSource;
	 std::string FragmentShaderSource;
	 unsigned int ShaderProgram,VAO,VBO,CBO;

public:
	
	void ClearScreen();
	void InitializeGraphics();
	void SetWindowICON();
	void Initilize_opengl();
	unsigned int CompileShaderFromSource(unsigned int shader_id, std::string& src);
	unsigned int CreateShaderFromStrings(std::string& VertexShader, std::string& fragmentshader);
	void drawTriangle();

public:
	 std::string get_vertex()const;
	 std::string get_fragment()const;

};

