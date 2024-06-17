#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "camera.h"
#include "texture.h"

#include "model.h"

#include "vertex.h"
#include "userinput.h"

#include <vector>
#include <iostream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Vertex vertices[] =
{
    //     COORDINATES     /        COLORS          /    NORMALS       /      TexCoord        //
    Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.05f, 0.05f), 	  glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(0.0f, 0.0f)},// Bottom side
    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(0.0f, 1.0f) },// Bottom side
    Vertex{glm::vec3( 0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(1.0f, 1.0f) },// Bottom side
    Vertex{glm::vec3( 0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.0f, -1.0f, 0.0f),        glm::vec2(1.0f, 0.0f) },// Bottom side

    Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.05f, 0.05f), 	 glm::vec3(-0.8f, 0.5f,  0.0f),       glm::vec2( 0.0f, 0.0f) },// Left Side
    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	 -glm::vec3(0.8f, 0.5f,  0.0f),        glm::vec2(1.0f, 0.0f) },// Left Side
    Vertex{glm::vec3( 0.0f, 0.8f,  0.0f),     glm::vec3(0.83f, 0.05f, 0.05f),	 -glm::vec3(0.8f, 0.5f,  0.0f),        glm::vec2(0.5f, 1.0f) },// Left Side

    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.0f, 0.5f, -0.8f),        glm::vec2(1.0f, 0.0f) },// Non-facing side
    Vertex{glm::vec3( 0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.0f, 0.5f, -0.8f),        glm::vec2(0.0f, 0.0f) },// Non-facing side
    Vertex{glm::vec3( 0.0f, 0.8f,  0.0f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.0f, 0.5f, -0.8f),        glm::vec2(0.5f, 1.0f) },// Non-facing side

    Vertex{glm::vec3( 0.5f, 0.0f, -0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.8f, 0.5f,  0.0f),        glm::vec2(0.0f, 0.0f) },// Right side
    Vertex{glm::vec3( 0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.8f, 0.5f,  0.0f),        glm::vec2(1.0f, 0.0f) },// Right side
    Vertex{glm::vec3( 0.0f, 0.8f,  0.0f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.8f, 0.5f,  0.0f),        glm::vec2(0.5f, 1.0f) },// Right side

    Vertex{glm::vec3( 0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.0f, 0.5f,  0.8f),        glm::vec2(1.0f, 0.0f) },// Facing side
    Vertex{glm::vec3(-0.5f, 0.0f,  0.5f),     glm::vec3(0.83f, 0.05f, 0.05f), 	 glm::vec3( 0.0f, 0.5f,  0.8f),       glm::vec2( 0.0f, 0.0f) },// Facing side
    Vertex{glm::vec3( 0.0f, 0.8f,  0.0f),     glm::vec3(0.83f, 0.05f, 0.05f),	  glm::vec3(0.0f, 0.5f,  0.8f),        glm::vec2(0.5f, 1.0f) },// Facing side
};

unsigned int indices[] =
{
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
};


int main(void)
{
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    // set opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(600, 600, "Opengl Playground", NULL, NULL);
    if (!window)
    {
        std::cout << "fail to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "fail to init glew" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // opengl config
    glViewport(0, 0, 600, 600);
    glClearColor(0.05f, 0.05f, 0.05f, 0.05f);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    UserInput userInput(window);

    /* init camera(position, center, up) */
    Camera camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    /* init shaders and textures */
    Shader pirimitShader("./res/simple.vs", "./res/simple.fs");
    pirimitShader.bind();
    Texture textures[] =
    {
        Texture("./res/brick.png", 0)
    };

    std::vector<Vertex> vert(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector<unsigned int> ind(indices, indices + sizeof(indices) / sizeof(unsigned int));
    std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

    for (size_t i = 0; i < tex.size(); i++)
    {
        tex[i].bind();
        pirimitShader.setUniform1i("tex" + std::to_string(i), tex[i].unitID);
    }

    Mesh pirimitMesh(vert, ind, tex);

    // set uniform
    pirimitShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
    pirimitShader.setUniformMatrix4fv("model", glm::value_ptr(glm::mat4(1.0f)));
    pirimitShader.unbind();

    /* load model */
    Model model("./res/model/nanosuit.obj");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        userInput.handleInput(camera);
        userInput.handleMouse(window, camera);


        /* draw call */
        model.draw(pirimitShader, camera);

        pirimitMesh.draw(pirimitShader, camera);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}