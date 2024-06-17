#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#include "texture.h"
#include <vector>

class Model
{
public:
	std::vector<Mesh> meshes;
	std::vector<Texture> t;

	Model(const std::string& path);

	void draw(Shader& shader, Camera& camera);
private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};