#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#include "texture.h"
#include <vector>
#include <memory>

class Model
{
public:
	std::vector<Mesh> meshes;
	std::vector<Texture> textureLoaded;
	std::string directory;

	unsigned int textureCount = 1;

	Model(const std::string& path);
	~Model();

	void draw(Shader& shader, Camera& camera);
private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Vertex> processVertices(aiMesh* mesh, const aiScene* scene);
	std::vector<unsigned int> processIndices(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> processTexture(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};