#include <GL/glew.h>

#include "fbo.h"

FBO::FBO()
{
	glGenFramebuffers(1, &fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

FBO::~FBO()
{
	glDeleteFramebuffers(1, &fboID);
}

void FBO::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

void FBO::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
