#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "external/stb/stb_image.h"

#include "texture.h"
#include "model.h"

#include <iostream>
#include <memory>

Model::Model(const std::string& path)
{
	loadModel(path);
}

Model::~Model()
{
    for (size_t i = 0; i < meshes.size(); i++)
    {
        glDeleteVertexArrays(1, &(meshes[i].vao.vaoID));
    }

    for (size_t i = 0; i < textureLoaded.size(); i++)
    {
        glDeleteTextures(1, &(textureLoaded[i].unitID));
    }
}

void Model::draw(Shader& shader, Camera& camera)
{
    for (size_t i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader, camera);
    }
}

void Model::loadModel(const std::string& path)
{
    /* load model */
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}


Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    
    std::vector<Vertex> vertices = processVertices(mesh, scene);
    std::vector<unsigned int> indices = processIndices(mesh, scene);
    std::vector<Texture> textures = processTexture(mesh, scene);
    
    return Mesh(vertices, indices, textures);
}


std::vector<Vertex> Model::processVertices(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;

    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector(0.0f, 0.0f, 0.0f);

        // position
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        // texture coordinate
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec(0.0f, 0.0f);
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord = vec;
        }
        else
        {
            vertex.texCoord = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }
    return vertices;
}

std::vector<unsigned int> Model::processIndices(aiMesh* mesh, const aiScene* scene)
{
    std::vector<unsigned int> indices;
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    return indices;
}

std::vector<Texture> Model::processTexture(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Texture> textures;

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> ambientMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_ambient");
    textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    return textures;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString path;
        mat->GetTexture(type, i, &path);
        bool skip = false;

        for (unsigned int j = 0; j < textureLoaded.size(); j++)
        {
            if (std::strcmp(textureLoaded[j].path.data(), path.C_Str()) == 0)
            {
                //textures.push_back(textureLoaded[j]);
                skip = true; 
                break;
            }
        }

        if (!skip)
        {
            Texture texture(directory + '/' + path.C_Str(), textureCount);
            texture.type = typeName;
            texture.path = path.C_Str();
            textures.push_back(texture);
            textureLoaded.push_back(texture);
            textureCount += 1;
        }
    }

    return textures;
}
