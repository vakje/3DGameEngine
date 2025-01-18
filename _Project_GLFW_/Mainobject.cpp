#include "Mainobject.h"

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
