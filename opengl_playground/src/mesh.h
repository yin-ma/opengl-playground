#pragma once

#include "vertex.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include <vector>

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	VAO vao;
	VBO vbo;
	EBO ebo;

	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
	~Mesh();
	void draw(Shader& shader, Camera& camera);
};