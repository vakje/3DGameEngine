#pragma once
#include <GL/glew.h>
#include "../External/stb/stb_image.h"
#include <string>
#include <iostream>
#include <filesystem>

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