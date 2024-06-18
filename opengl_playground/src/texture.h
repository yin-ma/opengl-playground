#pragma once

#include <assimp/Importer.hpp>
#include <string>

class Texture
{
public:
	unsigned int unitID;
	std::string type;
	std::string path;

	Texture();
	Texture(const std::string& filepath, unsigned int unit);

	void bind();
	void unbind();
};