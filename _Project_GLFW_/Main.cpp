#include <iostream>
#include "WindowComponent.h"
#include "Game.h"

const int WIDTH = 2560;
const int HEIGHT = 1440;
const char* TITLE = "3D GAME ENGINE";

std::vector<float> Vertices;
std::vector<unsigned int> Indices;
std::vector<float>UVcoordinates;

Materials material;
Meshes model;
std::ostream& operator<<( std::ostream& os, const Materials& mat) {
	return os <<"(" << mat.m_Materialname << "," << mat.m_Diffusecolor << ")";	 
}
void TexturedObjectFileParser(const std::string& filename, std::vector<float>& Vertices, std::vector<unsigned int>& Indices,
	std::vector<float>&UVcoordinates)
{
	//this line makes full path of the file must be like ..root\\user\\tools\\file.obj
	std::filesystem::path Toolspath = std::filesystem::current_path() / "TOOLS" / filename;
	// this must take and transform that in string
	std::string PATH = Toolspath.string();
	//this must split the string and take last file
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
	std::getline(file, line);


	while (std::getline(file, line))
	{
		
		if (line[0] == 'v' and line[1] != 't')
		{
			StringV = UTils::SplitString(line, " ");
		
			for (size_t i = 1; i<StringV.size(); i++)
			{				
				Vertices.push_back(std::stof(StringV[i]));						
			}			
		}
		else if (line.substr(0, 2) == "vt")
		{				
			StringUV = UTils::SplitString(line, " ");

		    for (size_t i=1; i<StringUV.size(); i++)
		    {										 
				UVcoordinates.push_back(std::stof(StringUV[i]));									
		    }			
		}	
		else if (line[0] == 'f')
		{

			StringI = UTils::SplitString(line, " ");

			
			for (size_t i =1; i<StringI.size();i++)
			{
				    // 3/1,2/1,3/2 
				
					if (StringI[i].size() == 1)
					{					
						//part is index now
						Indices.push_back(std::stoul(StringI[i]) - 1);
						std::cout << "parsed obj file that contains only indices\n";

					}
					else if (StringI[i].size() >= 3)
					{
						//now part is multiple indices
						StringIV = UTils::SplitString(StringI[i],"/");

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
void MTLfileparser(const std::string& filename, std::string& newmtl,std::string& map_kd,
  std::unordered_map<std::string,Materials>&materials)
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
	
	while(std::getline(file,line))
	{	
		std::istringstream iss(line);
		std::string keyword;
		iss >> keyword;
		if (keyword == "newmtl") {
			
			matnames = UTils::SplitString(line," ");
			model.m_materials[matnames[1]] = Materials{ matnames[1],"" };
		}
		else if (keyword == "map_Kd") {
			textnames = UTils::SplitString(line, " ");
			model.m_materials[matnames[1]].m_Diffusecolor = textnames[1];
			
		}
	}
	
}

int main()
{
	try {
		
		Game game;
		Window win(WIDTH, HEIGHT, TITLE);
		int frames = 0;

		double lastTime = glfwGetTime() * 1000.0;
		game.Initilize();
		const double FrameDelay = 1000.0 / 75;//making framedelay 
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(Window::m_mywindow))
		{

			/* Render here */
			game.Clear();
			/* Swap front and back buffers */
			game.MainCharacter();
			glfwSwapBuffers(Window::m_mywindow);
			/* Poll for and process events */
			glfwPollEvents();
			//currenttime in the loop
			double currentTime = glfwGetTime() * 1000.0;
			//adding frames 
			frames++;
			//if the time in the loop - time before loop  is more than 1 miliseconds
			if (currentTime - lastTime >= 1000.0) // Print every second
			{
				//print out fps 
				std::cout << "FPS: " << frames << std::endl;
				//assigne to 0 to make it default again
				frames = 0;
				// and assingn to the timer before loop to update the value 
				lastTime = currentTime;
			}


		}
	}catch(std::exception& ex)
	{
		std::cerr << "Fatal error occured:" << ex.what() << "\n";
	}

	std::cout << "-----------------------------------------------\n" << std::flush;


	TexturedObjectFileParser("cubeTextured.obj", Vertices,Indices,UVcoordinates);

	std::cout << "\n-----------------UVCoords----------------------\n";
	std::cout << "UVcoordinates size: " << UVcoordinates.size() << "\n";
	for (auto& item : UVcoordinates) {
		std::cout << std::fixed << std::setprecision(6) << item << "\n";
	}
	std::cout << "\n-----------------Vertices----------------------\n";
	std::cout << "vertices size: " << Vertices.size() << "\n";
	std::for_each(Vertices.begin(), Vertices.end(),[](float x){std::cout<<x<<" "; });
	std::cout << "\n-----------------Indices----------------------\n";
	std::for_each(Indices.begin(), Indices.end(), [](float x) {std::cout << x << " "; });
	
	

	MTLfileparser("TexturedCube.mtl", material.m_Materialname, material.m_Diffusecolor, model.m_materials);

	
	for (auto& pair : model.m_materials) {
		std::cout << "(" << pair.first << "," << pair.second << ")\n";
	}
     
}