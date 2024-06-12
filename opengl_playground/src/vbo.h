#pragma once

class VBO
{
public:
	unsigned int vboID;

	VBO(const float* vertices, unsigned int size);
	~VBO();

	void bind();
	void unbind();
};