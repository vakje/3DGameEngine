//needed to generate implemenations for stbimage.h
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture(GLenum TextureTarget, const std::filesystem::path& filename)
{
	m_Texturetarget = TextureTarget;
	m_Texturepath = filename;
}

bool Texture::load()
{
    // Flip the image vertically so it matches OpenGL's coordinate system
    stbi_set_flip_vertically_on_load(0);

    // Load the image
    int width = 0, height = 0, channels = 0;
    unsigned char* image_data = stbi_load(m_Texturepath.string().c_str(), &width, &height, &channels, 0);
    

    if (!image_data)
    {
        std::cerr << "Cannot load texture from path: " << m_Texturepath.string()
            << " | Reason: " << stbi_failure_reason() << "\n";
        return false;
    }
    std::cout << "Loaded texture: " << m_Texturepath.string()
        << " | Width: " << width << ", Height: " << height
        << ", Channels: " << channels << "\n";

    // Determine OpenGL format
    GLenum format = 0;
    if (channels == 1) format = GL_RED;
    else if (channels == 3) format = GL_RGB;
    else if (channels == 4) format = GL_RGBA;
    else
    {
        std::cerr << "Unsupported number of channels: " << channels << "\n";
        stbi_image_free(image_data);
        return false;
    }

    // Generate and bind texture
    glGenTextures(1, &m_TextureObject);
    glBindTexture(m_Texturetarget, m_TextureObject);

    if (m_Texturetarget == GL_TEXTURE_2D)
    {
        
        glTexImage2D(m_Texturetarget, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);

        // Set texture filtering and wrapping
        glTexParameteri(m_Texturetarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_Texturetarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_Texturetarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(m_Texturetarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    else
    {
        std::cerr << "Texture target not supported\n";
        stbi_image_free(image_data);
        return false;
    }

    glBindTexture(m_Texturetarget, 0);

    // Free image memory
    stbi_image_free(image_data);
    

    return true;
}

void Texture::bind(GLenum Textureunit)
{
	glActiveTexture(Textureunit);
	glBindTexture(m_Texturetarget, m_TextureObject);
}
