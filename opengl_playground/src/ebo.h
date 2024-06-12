#pragma once
#include "GL/glew.h"

class EBO
{
public:
	unsigned int eboID;
	EBO(unsigned int* indices, unsigned int size);
	~EBO();
	void bind();
	void unbind();
};