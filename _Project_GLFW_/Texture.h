#pragma once
#include <GL/glew.h>
#include "../External/stb/stb_image.h"
#include <string>
#include <iostream>

class Texture
{
	std::string m_Texturename;
	std::string m_Texturepath;
	unsigned int m_TextureObject;
	GLenum m_Texturetarget;
public:
	Texture(GLenum TextureTarget, const std::string& filename);

	bool load();

	void bind(GLenum Textureunit);

};