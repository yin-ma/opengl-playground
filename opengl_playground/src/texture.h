#pragma once

#include <string>

class Texture
{
public:
	unsigned int textureID;
	unsigned int unitID;

	Texture(const std::string& filepath, unsigned int slot, unsigned int unit);

	void bind();
	void unbind();
};