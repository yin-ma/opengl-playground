#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "vbo.h"
#include "ebo.h"

#include <iostream>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
    : vao(), vbo(vertices), ebo(indices)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
    
    vao.bind();

    // layout
    // position, color, normal, texture
    vbo.bind();
    ebo.bind();
    vbo.setLayoutf(0, 3, sizeof(Vertex), 0);
    vbo.setLayoutf(1, 3, sizeof(Vertex), 3);
    vbo.setLayoutf(2, 3, sizeof(Vertex), 6);
    vbo.setLayoutf(3, 2, sizeof(Vertex), 9);

    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

Mesh::~Mesh()
{
}


void Mesh::draw(Shader& shader, Camera& camera)
{
    vao.bind();
    shader.bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        if (textures[i].type == "texture_diffuse")
        {
            shader.setUniform1i("texture_diffuse" + std::to_string(numDiffuse), i);
            numDiffuse += 1;
        }
        else if (textures[i].type == "texture_specular")
        {
            shader.setUniform1i("texture_specular" + std::to_string(numSpecular), i);
            numSpecular += 1;
        }
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].unitID);
    }

    shader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.unbind();
    shader.unbind();

}
