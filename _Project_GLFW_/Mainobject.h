#pragma once
#include "Renderer.h"


class Object 
{

private:
	std::string name;
	std::string path;

public:
	void objfileparser(const std::string& path);
public:
	Object(const std::string& name, const std::string& path);
	const std::string& get_name()const;
	const std::string& get_path()const;

};
