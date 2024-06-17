#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "vertex.h"


class VBO
{
public:
	unsigned int vboID;

	VBO(std::vector<Vertex>& vertices);
	~VBO();

	void bind();
	void unbind();
	void setLayoutf(unsigned int location, int size, size_t stride, int index);
};