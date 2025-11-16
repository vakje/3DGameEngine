#pragma once
#include <GL/glew.h>
#include "../External/stb/stb_image.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>

class Texture
{
	std::string m_Texturename;
	std::filesystem::path m_Texturepath;
	unsigned int m_TextureObject;
	GLenum m_Texturetarget;
public:
	Texture(GLenum TextureTarget, const std::filesystem::path& filename);

	bool load();

	void bind(GLenum Textureunit);

};

//abstraction for storing data for materials currently storing only texture png and its name 
struct Materials
{
	std::string m_Materialname;
	std::string m_Diffusecolor;//map_kd
	
};


struct Meshes 
{
	//todo this struct should represent entire loaded model like cube in my case 
	//it should have data that represents meshe in engine
	//possibly it should also have array where we will store all of our objects/models/meshes for engine
	std::unordered_map<std::string, Materials> m_materials;

};