#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "vbo.h"
#include "ebo.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
    :vbo(vertices), ebo(indices)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

    vao.bind();
    vbo.bind();
    ebo.bind();

    // layout
    vbo.setLayoutf(0, 3, sizeof(Vertex), 0);
    vbo.setLayoutf(1, 3, sizeof(Vertex), 3);
    vbo.setLayoutf(2, 3, sizeof(Vertex), 6);
    vbo.setLayoutf(3, 2, sizeof(Vertex), 9);

    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}


void Mesh::draw(Shader& shader, Camera& camera)
{
    vao.bind();
    shader.bind();

    shader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
