#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "camera.h"
#include "texture.h"

#include "userinput.h"

#include <iostream>


float vertices[] =
{
    //     COORDINATES     /        COLORS          /    NORMALS       /      TexCoord        //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f, 	  0.0f, -1.0f, 0.0f,        0.0f, 0.0f,// Bottom side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	  0.0f, -1.0f, 0.0f,        0.0f, 1.0f,// Bottom side
     0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	  0.0f, -1.0f, 0.0f,        1.0f, 1.0f,// Bottom side
     0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f,	  0.0f, -1.0f, 0.0f,        1.0f, 0.0f,// Bottom side
                                                                                
    -0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f, 	 -0.8f, 0.5f,  0.0f,        0.0f, 0.0f,// Left Side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	 -0.8f, 0.5f,  0.0f,        1.0f, 0.0f,// Left Side
     0.0f, 0.8f,  0.0f,     0.83f, 0.05f, 0.05f,	 -0.8f, 0.5f,  0.0f,        0.5f, 1.0f,// Left Side
                                                                                
    -0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	  0.0f, 0.5f, -0.8f,        1.0f, 0.0f,// Non-facing side
     0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	  0.0f, 0.5f, -0.8f,        0.0f, 0.0f,// Non-facing side
     0.0f, 0.8f,  0.0f,     0.83f, 0.05f, 0.05f,	  0.0f, 0.5f, -0.8f,        0.5f, 1.0f,// Non-facing side
                                                                                
     0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	  0.8f, 0.5f,  0.0f,        0.0f, 0.0f,// Right side
     0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f,	  0.8f, 0.5f,  0.0f,        1.0f, 0.0f,// Right side
     0.0f, 0.8f,  0.0f,     0.83f, 0.05f, 0.05f,	  0.8f, 0.5f,  0.0f,        0.5f, 1.0f,// Right side
                                                                                
     0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f,	  0.0f, 0.5f,  0.8f,        1.0f, 0.0f,// Facing side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f, 	  0.0f, 0.5f,  0.8f,        0.0f, 0.0f,// Facing side
     0.0f, 0.8f,  0.0f,     0.83f, 0.05f, 0.05f,	  0.0f, 0.5f,  0.8f,        0.5f, 1.0f,// Facing side
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
    glClearColor(0.02f, 0.02f, 0.02f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    UserInput userInput(window);

    /* init camera(position, center, up) */
    Camera camera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    /* init shaders and textures */
    Shader pirimitShader("./res/simple.vs", "./res/simple.fs");
    pirimitShader.bind();
    Texture brickTexture("./res/brick.png", 0);
    brickTexture.bind();
    pirimitShader.setUniform1i("tex0", brickTexture.unitID);


    /* init buffers& layouts */
    VAO pirimitVao;
    VBO pritimitVbo(vertices, sizeof(vertices));
    EBO pirimitEbo(indices, sizeof(indices));
    pirimitVao.bind();
    pritimitVbo.bind();
    pirimitEbo.bind();

    // layout
    pritimitVbo.setLayoutf(0, 3, 11, 0);
    pritimitVbo.setLayoutf(1, 3, 11, 3);
    pritimitVbo.setLayoutf(2, 3, 11, 6);
    pritimitVbo.setLayoutf(3, 2, 11, 9);


    // set uniform
    glm::mat4 cameraMat = camera.getMatrix();
    glm::mat4 pirimitModelMat = glm::mat4(1.0f);
    pirimitShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(cameraMat));
    pirimitShader.setUniformMatrix4fv("model", glm::value_ptr(pirimitModelMat));

    pirimitShader.unbind();
    pirimitVao.unbind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        userInput.handleInput(camera);
        userInput.handleMouse(window, camera);

        cameraMat = camera.getMatrix();

        /* draw call */

        // draw pirimit
        pirimitVao.bind();
        pirimitShader.bind();
        pirimitShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(cameraMat));
        glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}