#include "Mainobject.h"

//todo parser
//for example string path = "file.obj"
void Object::objfileparser(const std::string& path)
{
	//this line makes full path of the file must be like ..root\\user\\tools\\file.obj
	std::filesystem::path Toolspath = std::filesystem::current_path() / "TOOLS" / path;
	// this must take and transform that in string
	std::string PATH = Toolspath.string();
	//this must split the string and take last file
	std::string splitedtoken = UTils::SplitString(PATH, "\\");
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
    std::list<float> Vertices;
	std::list<float> Indices;
	//std::getline(file, line);
	//while (!file.eof())
	//{
	//	
	//	if(line.find('v') != std::string::npos)
	//	{
	//		//todo parse data and then write it to the list vertices
	//		std::getline(file, v, ' ');
	//		Vertices.push_back(stof(v));
	//	    
	//	}
	//    if (line.find('f')!= std::string::npos)
	//	{
	//		//todo parse data and then write it to the list indices
	//		std::getline(file, i, ' ');
	//		Vertices.push_back(stof(i));
	//	}
	//	
	//}
	file.close();
	
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
