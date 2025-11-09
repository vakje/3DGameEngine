//needed to generate implemenations for stbimage.h
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& filename)
{
	m_Texturetarget = TextureTarget;
	m_Texturepath = filename;
}

bool Texture::load()
{
	//first flipping the texture

	stbi_set_flip_vertically_on_load(1);
	
	//defining image itself loading texture from file
	int width = 0, height = 0, bitsperpixel = 0;
	unsigned char* image_data = stbi_load(m_Texturepath.c_str(),&width,&height,&bitsperpixel,0);

	if(!image_data)
	{
		std::cerr << "Cant Load texture from this file path" << m_Texturepath.c_str() << " because of:"
			<< stbi_failure_reason() << "\n";
		return false;
	}
	std::cout << "Width:" << width << ",Height:" << height << ",Bitsperpixel:" << bitsperpixel << "\n";
	
	glGenTextures(1, &m_TextureObject);
	glBindTexture(m_Texturetarget, m_TextureObject);
	
	if (m_Texturetarget == GL_TEXTURE_2D)
	{
		//GL_texture_2d out 2d texture
		//mip levels 
		//format of textures types channels of colors
		//sizes width height
		//image type 
		//texture type 
		//image itself
		glTexImage2D(m_Texturetarget, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);

	}else
	{
		std::cerr << "Support for texture target is not implemented" << "\n";
		return false;
	}
	
	glTexParameteri(m_Texturetarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_Texturetarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(m_Texturetarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(m_Texturetarget, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//
	glBindTexture(m_Texturetarget, 0);

	stbi_image_free(image_data);

	
	return true;
}

void Texture::bind(GLenum Textureunit)
{
	glActiveTexture(Textureunit);
	glBindTexture(m_Texturetarget, m_TextureObject);
}
