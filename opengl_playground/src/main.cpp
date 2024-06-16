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
    //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	 1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

    -0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	 1.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
     0.0f, 0.8f,  0.0f,     0.83f, 0.05f, 0.05f,	 0.5f, 1.0f,     -0.8f, 0.5f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	 1.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
     0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
     0.0f, 0.8f,  0.0f,     0.83f, 0.05f, 0.05f,	 0.5f, 1.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

     0.5f, 0.0f, -0.5f,     0.83f, 0.05f, 0.05f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
     0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f,	 1.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
     0.0f, 0.8f,  0.0f,     0.83f, 0.05f, 0.05f,	 0.5f, 1.0f,      0.8f, 0.5f,  0.0f, // Right side

     0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f,	 1.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.05f, 0.05f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
     0.0f, 0.8f,  0.0f,     0.83f, 0.05f, 0.05f,	 0.5f, 1.0f,      0.0f, 0.5f,  0.8f  // Facing side
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


float lightVertices[] =
{ //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};


unsigned int lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};


float planeVertices[] =
{ //     COORDINATES     // normal
    -4.0f, 0.0f, -4.0f, 0.0f, 1.0f, 0.0f,
    -4.0f, 0.0f, 4.0f, 0.0f, 1.0f, 0.0f,
     4.0f, 0.0f, -4.0f, 0.0f, 1.0f, 0.0f,
     4.0f, 0.0f, 4.0f, 0.0f, 1.0f, 0.0f,
};


unsigned int planeIndices[] =
{
    0, 1, 2,
    2, 1, 3,
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

    // init camera(position, center, up)
    Camera camera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
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
    pritimitVbo.setLayoutf(3, 3, 11, 8);

    // init shader
    Shader pirimitShader("./res/vertexShader.shader", "./res/fragmentShader.shader");
    pirimitShader.bind();
    Texture brickTexture("./res/brick.png", GL_TEXTURE0, 0);
    brickTexture.bind();
    pirimitShader.setUniform1i("tex0", brickTexture.unitID);

    // set uniform
    glm::mat4 cameraMat = camera.getMatrix();
    glm::mat4 pirimitModelMat = glm::mat4(1.0f);
    pirimitShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(cameraMat));
    pirimitShader.setUniformMatrix4fv("model", glm::value_ptr(pirimitModelMat));

    pirimitShader.unbind();
    pirimitVao.unbind();

    /* init plane */
    VAO planeVAO;
    VBO planeVBO(planeVertices, sizeof(planeVertices));
    EBO planeEBO(planeIndices, sizeof(planeIndices));
    planeVAO.bind();
    planeVBO.bind();
    planeEBO.bind();

    planeVBO.setLayoutf(0, 3, 6, 0);
    planeVBO.setLayoutf(1, 3, 6, 3);

    Shader planeShader("./res/planeVertex.shader", "./res/planeFragment.shader");
    planeShader.bind();

    glm::mat4 planeModel = glm::mat4(1.0f);
    planeShader.setUniformMatrix4fv("model", glm::value_ptr(planeModel));
    planeShader.setUniformMatrix4fv("cameraMatrix", glm::value_ptr(cameraMat));
    planeShader.setUniform3fv("cameraPosition", glm::value_ptr(camera.position));
 
    /* init light source */
    VAO lightVAO;
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    lightVAO.bind();
    lightVBO.bind();
    lightEBO.bind();

    lightVBO.setLayoutf(0, 3, 3, 0);

    Shader lightShader("./res/lightVertex.shader", "./res/lightFragment.shader");
    lightShader.bind();

    glm::vec4 lightColor(0.9f, 0.9f, 0.9f, 1.0f);
    glm::vec3 lightPosition(0.8f, 0.8f, 0.8f);
    glm::mat4 lightModel = glm::translate(lightPosition);

    lightShader.setUniformMatrix4fv("model", glm::value_ptr(lightModel));
    lightShader.setUniformMatrix4fv("cameraMatrix", glm::value_ptr(cameraMat));
    lightShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));

    lightShader.unbind();
    lightVAO.unbind();

    /* init shaders uniform */
    pirimitShader.bind();
    pirimitShader.setUniform3fv("lightPos", glm::value_ptr(lightPosition));
    pirimitShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
    pirimitShader.setUniform3fv("camPos", glm::value_ptr(camera.position));
    pirimitShader.unbind();

    planeShader.bind();
    planeShader.setUniform3fv("lightPosition", glm::value_ptr(lightPosition));
    planeShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
    planeShader.unbind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        userInput.handleInput(camera);
        userInput.handleMouse(window, camera);

        cameraMat = camera.getMatrix();

        /* draw call */

        // draw light
        glm::vec3 lPos = glm::rotate(lightPosition, glm::radians((float)glfwGetTime()*50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        lightVAO.bind();
        lightShader.bind();
        lightModel = glm::translate(lPos);
        lightShader.setUniformMatrix4fv("model", glm::value_ptr(lightModel));
        lightShader.setUniformMatrix4fv("cameraMatrix", glm::value_ptr(cameraMat));
        glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);

        // draw pirimit
        pirimitVao.bind();
        pirimitShader.bind();
        pirimitShader.setUniform3fv("camPos", glm::value_ptr(camera.position));
        pirimitShader.setUniform3fv("lightPos", glm::value_ptr(lPos));
        pirimitShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(cameraMat));
        glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, 0);

        // draw plane
        planeVAO.bind();
        planeShader.bind();
        planeShader.setUniform3fv("cameraPosition", glm::value_ptr(camera.position));
        planeShader.setUniform3fv("lightPosition", glm::value_ptr(lPos));
        planeShader.setUniformMatrix4fv("cameraMatrix", glm::value_ptr(cameraMat));
        glDrawElements(GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}