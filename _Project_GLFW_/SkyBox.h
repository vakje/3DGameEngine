#pragma once

#include "glad/glad.h"
#include "../External/stb/stb_image.h"
#include <vector>
#include <String>
#include <array>
#include <format>
#include <filesystem>

class SkyBox
{
public:
	std::vector<std::string> m_Faces; // faces of the cubemap
	std::array<float, 108> m_SkyBoxVertices; // 108 vertices for each face in our cube

	
	SkyBox();

	unsigned int loadCubemap();

};

