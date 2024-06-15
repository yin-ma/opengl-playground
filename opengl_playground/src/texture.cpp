#include "texture.h"
#include "external/stb/stb_image.h"
#include "GL/glew.h"

#include <iostream>
#include <string>


Texture::Texture(const std::string& filepath, unsigned int slot, unsigned int unit)
{
    unitID = unit;
    // convert image to byte
    int width, height, channel;
    const char* src = filepath.c_str();
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(src, &width, &height, &channel, 0);

    if (!bytes)
    {
        std::cout << "img fail to loaded" << std::endl;
    }

    glGenTextures(1, &textureID);
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, textureID);
}


void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}