#pragma once

#include <glm/glm.hpp>

#include "texture.h"
#include "vao.h"
#include "camera.h"
#include "shader.h"
#include <vector>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	VAO vao;

	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
	void draw(Shader& shader, Camera& camera);
};