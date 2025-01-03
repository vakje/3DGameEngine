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
	 unsigned int ShaderProgram,VAO,VBO,CBO,EBO;	
	 //ShaderProgram actual shaders that are compiled are stored in here
	 //VAO vertex atribute
	 //vertex buffer
	 // color buffer
	 std::map<std::string, int> Uniforms;
public:
	
	void ClearScreen();
	void InitializeGraphics();
	void SetWindowICON();
	void Initilize_opengl();
	unsigned int CompileShaderFromSource(unsigned int shader_id, std::string& src);
	unsigned int CreateShaderFromStrings(std::string& VertexShader, std::string& fragmentshader);
	void drawTriangle();
	std::pair<std::string ,std::string> ReadFromShaderFile(const std::string& path);
	void addUniform(std::string uniform);
	void setUniformi(std::string Key,int value);
	void setUniformf(std::string Key, float value);
	void setUniformVector3(std::string Key, Vector3F<float>& value);
	void setUniformiMatrix4(std::string Key, Matrix<float>& value);
	~Renderer();

public:
	 std::string get_vertex()const;
	 std::string get_fragment()const;
	 

};

