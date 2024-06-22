#pragma once

#include <string>

class Texture
{
public:
	unsigned int unitID;
	std::string type;
	std::string path;

	Texture();
	~Texture();
	Texture(const std::string& filepath, unsigned int unit);
};