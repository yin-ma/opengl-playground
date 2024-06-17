#include "GL/glew.h"
#include "vao.h"
#include <iostream>

VAO::VAO()
{
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

}

VAO::~VAO()
{
	// due to model call, memory allocated makes wired thing happened...
	/*glDeleteVertexArrays(1, &vaoID);*/
}

void VAO::bind()
{
	glBindVertexArray(vaoID);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}
