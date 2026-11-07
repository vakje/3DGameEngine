#include "SkyBox.h"
const std::filesystem::path current = std::filesystem::current_path();
SkyBox::SkyBox()
{
	m_Faces = 
	{
		// right left 
        current.string() + "\\TOOLS\\SkyBox\\didgori\\px.png",
        current.string() + "\\TOOLS\\SkyBox\\didgori\\nx.png",
		// top bottom 
        current.string() + "\\TOOLS\\SkyBox\\didgori\\py.png",
        current.string() + "\\TOOLS\\SkyBox\\didgori\\ny.png",
		// front back
        current.string() + "\\TOOLS\\SkyBox\\didgori\\pz.png",
        current.string() + "\\TOOLS\\SkyBox\\didgori\\nz.png"
	};
	m_SkyBoxVertices =
	{
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
	};

}



unsigned int SkyBox::loadCubemap()
{
    std::vector<std::future<CubeMapFaces>> jobs;

    for (auto& p : m_Faces) 
    {
        jobs.push_back(std::async(std::launch::async, &SkyBox::loadFace, this, p));
    }

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);

    for (unsigned int i = 0; i < jobs.size(); i++) 
    {
        CubeMapFaces face = jobs[i].get();
        if (face.data)
        {
            GLenum format = (face.Channels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, face.width, face.height, 0, format, GL_UNSIGNED_BYTE, face.data);
            stbi_image_free(face.data);
        }
        else 
        {
            std::string message = std::format("Cubemap tex failed to load at path: {}", m_Faces[i], stbi_failure_reason());
            stbi_image_free(face.data);
            throw std::runtime_error(message);

        }

    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // generate the actual mipmap images to blur the image with this i can blur the image with function texturedlod
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    return textureID;
}

CubeMapFaces SkyBox::loadFace(const std::string& path)
{
    CubeMapFaces cmf;
   
    cmf.data = stbi_load(path.c_str(), &cmf.width, &cmf.height, &cmf.Channels, 0);
 

    return cmf;
}
