#pragma once

#include <string>

class Texture
{
public:
	unsigned int unitID;
	std::string type;
	std::string path;

	Texture(const std::string& filepath, unsigned int unit);
	~Texture();

	void bind();
	void unbind();
};