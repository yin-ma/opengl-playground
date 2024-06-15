#include <GL/glew.h>
#include "shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    shaderID = glCreateProgram();
    int sucess;
    char infoLog[512];

    // setup vertex shader
    std::string vertexShaderSource = parseShader(vertexShaderFilePath).c_str();
    std::string fragmentShaderSource = parseShader(fragmentShaderFilePath).c_str();

    const char* vertexSrc = vertexShaderSource.c_str();
    const char* fragmentSrc = fragmentShaderSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "vertex shader compile error :\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "fragment shader compile error :\n" << infoLog << std::endl;
    }

    // link shaders
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);

    glGetProgramiv(shaderID, GL_LINK_STATUS, &sucess);
    if (!sucess)
    {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "program linking error :\n" << infoLog << std::endl;
    }

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

void Shader::setUniform1i(const std::string& key, int value)
{
    glUniform1i(glGetUniformLocation(shaderID, key.c_str()), value);
}
