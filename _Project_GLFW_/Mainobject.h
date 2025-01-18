#pragma once
#include "Renderer.h"
#include <string>

class Object 
{

private:
	std::string name;
	std::string path;

public:
public:
	Object(const std::string& name, const std::string& path);
	const std::string& get_name()const;
	const std::string& get_path()const;

};
