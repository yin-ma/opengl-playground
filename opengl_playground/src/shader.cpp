#include <GL/glew.h>
#include "shader.h"

#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    shaderID = glCreateProgram();

    // setup vertex shader
    std::string vertexShaderSource = parseShader(vertexShaderFilePath).c_str();
    std::string fragmentShaderSource = parseShader(fragmentShaderFilePath).c_str();

    const char* vertexSrc = vertexShaderSource.c_str();
    const char* fragmentSrc = fragmentShaderSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);

    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


Shader::~Shader()
{
    glDeleteProgram(shaderID);
}

std::string Shader::parseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    std::string line;
    std::stringstream ss;

    while (std::getline(stream, line))
    {
        ss << line << "\n";
    }

    return ss.str();
}

void Shader::bind()
{
    glUseProgram(shaderID);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::setUniform1i(const std::string& uniform, int i)
{
    unsigned int uni = glGetUniformLocation(shaderID, uniform.c_str());
    glUniform1i(uni, i);
}