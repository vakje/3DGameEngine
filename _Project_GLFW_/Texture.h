#pragma once
#include <GL/glew.h>
#include "../External/stb/stb_image.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Util.h"
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


struct Materials
{
	std::string m_Materialname;
	std::string m_Diffusecolor;
	
};


struct Meshes 
{
	
	std::unordered_map<std::string, Materials> m_materials;
	std::vector<float> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<float>UVcoordinates;
	void TexturedObjectFileParser(const std::string& filename, std::vector<float>& Vertices, std::vector<unsigned int>& Indices,
		std::vector<float>& UVcoordinates)
	{
		
		std::filesystem::path Toolspath = std::filesystem::current_path() / "TOOLS" / filename;
	
		std::string PATH = Toolspath.string();
		
		std::string lastfile = UTils::SplitPath(PATH);
		std::cout << "Meshe's Name:  " << lastfile << "  " << std::endl;
		if (lastfile.find(".obj") == std::string::npos)
		{
			std::cout << "this is not a obj file" << std::endl;
		}
		std::ifstream file(PATH);

		if (!file.is_open())
		{
			std::cout << "file not found" << std::endl;
		}

		std::string line;
		std::vector<std::string> StringV;
		std::vector<std::string> StringI;
		std::vector<std::string> StringIV;
		std::vector<std::string> StringUV;


		std::string Mtl_filename;
		std::string keyword;
		std::getline(file, line);


		while (std::getline(file, line))
		{
			std::istringstream ss(line);

			if (line.substr(0, 6) == "mtllib")
			{
				ss >> std::ws;
				ss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
				ss >> Mtl_filename;
				std::cout << "mtl_filename:" << Mtl_filename;
			}
			if (line[0] == 'v' and line[1] != 't')
			{
				StringV = UTils::SplitString(line, " ");

				for (size_t i = 1; i < StringV.size(); i++)
				{
					Vertices.push_back(std::stof(StringV[i]));
				}
			}
			else if (line.substr(0, 2) == "vt")
			{
				StringUV = UTils::SplitString(line, " ");

				for (size_t i = 1; i < StringUV.size(); i++)
				{
					UVcoordinates.push_back(std::stof(StringUV[i]));
				}
			}
			else if (line[0] == 'f')
			{

				StringI = UTils::SplitString(line, " ");


				for (size_t i = 1; i < StringI.size(); i++)
				{
					

					if (StringI[i].size() == 1)
					{
						//part is index now
						Indices.push_back(std::stoul(StringI[i]) - 1);
						std::cout << "parsed obj file that contains only indices\n";

					}
					else if (StringI[i].size() >= 3)
					{
						//now part is multiple indices
						StringIV = UTils::SplitString(StringI[i], "/");

						for (auto& indeces : StringIV)
						{
							Indices.push_back(std::stoul(indeces) - 1);
						}
					}
				}
			}
		}
		file.close();
	}
	void MTLfileparser(const std::string& filename, std::string& newmtl, std::string& map_kd,
		std::unordered_map<std::string, Materials>& materials)
	{

		std::filesystem::path Toolspath = std::filesystem::current_path() / "TOOLS" / filename;

		std::string PATH = Toolspath.string();

		std::string lastfile = UTils::SplitPath(PATH);
		std::cout << "\nMeshe's material name is:  " << lastfile << "  " << std::endl;
		if (lastfile.find(".mtl") == std::string::npos)
		{
			std::cout << "this is not a mtl file" << std::endl;
		}
		std::ifstream file(PATH);

		if (!file.is_open())
		{
			std::cout << "file not found" << std::endl;
		}

		std::string line;
		std::vector<std::string>matnames;
		std::vector<std::string>textnames;
		std::string currentname;

		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string keyword;
			iss >> keyword;
			if (keyword == "newmtl") {

				matnames = UTils::SplitString(line, " ");
				m_materials[matnames[1]] = Materials{ matnames[1],"" };
			}
			else if (keyword == "map_Kd") {
				textnames = UTils::SplitString(line, " ");
				m_materials[matnames[1]].m_Diffusecolor = textnames[1];

			}
		}

	}

};