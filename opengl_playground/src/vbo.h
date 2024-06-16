#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VBO
{
public:
	unsigned int vboID;

	VBO(const float* vertices, unsigned int size);
	~VBO();

	void bind();
	void unbind();
	void setLayoutf(unsigned int location, int size, size_t stride, int index);
};