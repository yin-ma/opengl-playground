#include "mesh.h"
#include "vbo.h"
#include "ebo.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
	: vertices(vertices), indices(indices), textures(textures)
{
	vao.bind();
	VBO vbo(vertices);
	EBO ebo(indices);

	vbo.setLayoutf(0, 3, sizeof(Vertex), 0);
	vbo.setLayoutf(1, 3, sizeof(Vertex), 3);
	vbo.setLayoutf(2, 3, sizeof(Vertex), 6);
	vbo.setLayoutf(3, 2, sizeof(Vertex), 9);

	ebo.unbind();
	vbo.unbind();
	vao.unbind();
}


void Mesh::draw(Shader& shader, Camera& camera)
{
	vao.bind();
	shader.bind();

	for (size_t i = 0; i < textures.size(); i++)
	{
		textures[i].bind();
		shader.setUniform1i("tex0", textures[i].unitID);
	}

	shader.setUniform4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
	glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_INT, 0);
}
