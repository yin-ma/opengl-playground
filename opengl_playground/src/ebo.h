#pragma once
#include "GL/glew.h"

#include <vector>

class EBO
{
public:
	unsigned int eboID;
	EBO(std::vector<unsigned int>& indices);
	~EBO();
	void bind();
	void unbind();
};