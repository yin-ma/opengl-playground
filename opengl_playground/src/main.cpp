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

    glViewport(0, 0, 600, 600);
    
    // init buffers & layouts
    VAO vao;
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.bind();
    vbo.bind();
    ebo.bind();

    // layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    Shader shader("./res/vertexShader.shader", "./res/fragmentShader.shader");
    shader.bind();
    Texture texture("./res/brick.png", GL_TEXTURE0, 0);
    texture.bind();
    shader.setUniform1i("tex0", texture.unitID);

    // camera position, center, up
    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    int matLoc = glGetUniformLocation(shader.shaderID, "cameraMat");
    glm::mat4 cameraMat = camera.getMatrix();
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(cameraMat));

    int modelLoc = glGetUniformLocation(shader.shaderID, "model");
    glm::mat4 model = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    shader.unbind();
    vao.unbind();
 
    // init light source
    VAO lightVAO;
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    lightVAO.bind();
    lightVBO.bind();
    lightEBO.bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader lightShader("./res/lightVertex.shader", "./res/lightFragment.shader");
    lightShader.bind();

    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPosition(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::translate(lightPosition);

    int lightMatLoc = glGetUniformLocation(lightShader.shaderID, "model");
    int lightCamLoc = glGetUniformLocation(lightShader.shaderID, "cameraMatrix");
    int lightColorLoc = glGetUniformLocation(lightShader.shaderID, "lightColor");

    glUniformMatrix4fv(lightMatLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniformMatrix4fv(lightCamLoc, 1, GL_FALSE, glm::value_ptr(cameraMat));
    glUniform4fv(lightColorLoc, 1, glm::value_ptr(lightColor));

    lightShader.unbind();
    lightVAO.unbind();

    shader.bind();
    glUniform3fv(glGetUniformLocation(shader.shaderID, "lightPos"), 1, glm::value_ptr(lightPosition));
    glUniform4fv(glGetUniformLocation(shader.shaderID, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shader.shaderID, "camPos"), 1, glm::value_ptr(camera.position));
    shader.unbind();

    UserInput userInput(window);
    glClearColor(0.02f, 0.02f, 0.02f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        userInput.handleInput(camera);

        cameraMat = camera.getMatrix();

        /* draw call */
        vao.bind();
        shader.bind();
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(cameraMat));
        glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, 0);

        lightVAO.bind();
        lightShader.bind();
        glUniformMatrix4fv(lightCamLoc, 1, GL_FALSE, glm::value_ptr(cameraMat));
        glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}