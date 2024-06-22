#pragma once

#include <string>

class Texture
{
public:
	unsigned int unitID;
	unsigned int slot;
	std::string type;
	std::string path;

	Texture(const std::string& filepath, unsigned int unit);
	~Texture();
};