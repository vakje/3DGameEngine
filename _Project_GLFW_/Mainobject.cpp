#include "Mainobject.h"

//todo parser
//for example string path = "file.obj"
void Object::objfileparser(const std::string& path, std::vector<float> Vertices, std::vector<unsigned int> Indices)
{
	//this line makes full path of the file must be like ..root\\user\\tools\\file.obj
	std::filesystem::path Toolspath = std::filesystem::current_path() / "TOOLS" / path;
	// this must take and transform that in string
	std::string PATH = Toolspath.string();
	//this must split the string and take last file
	std::string splitedtoken = UTils::FileChecker(PATH, "\\");
	std::cout<<"this is the final splited thing:  "<<splitedtoken<<"  "<< std::endl;
	if(!splitedtoken.find(".obj"))
	{
		std::cout << "this is not a obj file" << std::endl;
	}
	std::ifstream file(PATH);
	 
	if (!file.is_open())
	{
		std::cout << "file not found" << std::endl;
	}

	std::string line;
	std::string v;
	std::string i;

	
   
	std::vector<std::string> StringV;
	std::vector<std::string> StringI;
	std::getline(file, line);
	
	
	while (std::getline(file, line))
	{
		
		if (line[0]== 'v')
		{
			

			//somehow in this chunck of code Indices are puted into the vector not vertices		
			StringV = UTils::splitString(line, " ");
			
			// transfer this data to original Indices vector
			//also parsing it to float 
			for (auto& V : StringV)
			{
				try {
					Vertices.push_back(std::stof(V));
				}
				catch (std::exception ex) 
				{
					//really nothing i can do with this one at this moment at least 
				}
			}
			

		}if (line[0] == 'f')
		{
			//somehow in this chunck of code vertices are puted into the vector not indices
			StringI = UTils::splitString(line, " ");
			
			// transfer this data to original vertex vector
			//also parsing it to float 
			for (auto& Index : StringI)
			{
				try {
					Indices.push_back(std::stoul(Index));
				}
				catch (std::exception ex) 
				{
					//really nothing i can do with this one at this moment at least 
				}
			}


		}
	}
	file.close();
	//this must be done due to the misleading Extra information in those vectors
	Vertices.erase(Vertices.end() - 1);
	Indices.erase(Indices.begin() + 0);
	std::cout <<"\n" << "------------------------this must be vertices----------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	for (const auto& v : Vertices) {
		std::cout << v << " ";
	}
	std::cout << "\n";
	std::cout << "\n" << "------------------------this must be Indices----------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	for (const auto& I : Indices) {
		std::cout << I << " ";
	}
	std::cout << "\n";
	unsigned int m_VAO = get_VAO();
	unsigned int m_VBO = get_VBO();
	unsigned int m_EBO = get_EBO();
	    //now giving this data to our GPU
		glGenVertexArrays(1, &m_VAO); 
		glBindVertexArray(m_VAO);




		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), &Vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int),
			&Indices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Unbind VAO 
		glBindVertexArray(0);
	
}

Object::Object(const std::string& name, const std::string& path)
{
	this->name = name;
	this->path = path;
}



const std::string& Object::get_name() const
{
	return name;
}

const std::string& Object::get_path() const
{
	return path;
}
