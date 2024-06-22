#include "external/stb/stb_image.h"
#include <assimp/Importer.hpp>
#include "GL/glew.h"

#include "texture.h"

#include <iostream>
#include <string>



Texture::Texture(const std::string& filepath, unsigned int unit)
{
    // convert image to byte
    int width, height, channel;
    stbi_set_flip_vertically_on_load(false);
    unsigned char* bytes = stbi_load(filepath.c_str(), &width, &height, &channel, 0);
    if (!bytes)
    {
        std::cout << "img fail to loaded" << std::endl;
    }

    glGenTextures(1, &unitID);
    glBindTexture(GL_TEXTURE_2D, unitID);

    if (channel == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    }
    else if (channel == 3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    }
    else if (channel == 1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
    }
    else
    {
        std::cout << "texture input has wrong channel number" << std::endl;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}
    

Texture::~Texture()
{
    //glDeleteTextures(1, &unitID);
}


void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, unitID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}