#include "GL/glew.h"
#include "vao.h"

VAO::VAO()
{
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &vaoID);
}

void VAO::bind()
{
	glBindVertexArray(vaoID);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}
