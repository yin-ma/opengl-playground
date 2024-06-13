#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:
	unsigned int shaderID;

	Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	~Shader();

	static std::string parseShader(const std::string& filePath);
	void bind();
	void unbind();

	void setUniform1i(const std::string& uniform, int i);
};