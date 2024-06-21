#pragma once

class FBO
{
public:
	unsigned int fboID;

	FBO();
	~FBO();

	void bind();
	void unbind();
};