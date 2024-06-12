#include "vbo.h"
#include "GL/glew.h"

VBO::VBO(const float* vertices, unsigned int size)
{
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &vboID);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
