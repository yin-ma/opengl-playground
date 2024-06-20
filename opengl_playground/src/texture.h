#pragma once

#include <assimp/Importer.hpp>
#include <string>

class Texture
{
public:
	unsigned int unitID = 0;
	std::string type;
	std::string path;

	Texture();
	~Texture();
	Texture(const std::string& filepath, unsigned int unit);

	void bind();
	void unbind();
};