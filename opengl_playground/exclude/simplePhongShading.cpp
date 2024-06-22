#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"
#include "external/stb/stb_image.h"
#include <assimp/Importer.hpp>

#include "pointLight.cpp"

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "vertex.h"
#include "userinput.h"

#include <vector>
#include <iostream>
#include <string>


const int SCR_WIDTH = 600;
const int SCR_HEIGHT = 600;

float planeVertices[] = {
    // positions            // normals         // texcoords
     25.0f, 0.0f,  25.0f,  0.0f, 1.0f, 0.0f,  2.0f,  0.0f,
    -25.0f, 0.0f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
    -25.0f, 0.0f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 2.0f,

     25.0f, 0.0f,  25.0f,  0.0f, 1.0f, 0.0f,  2.0f,  0.0f,
    -25.0f, 0.0f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 2.0f,
     25.0f, 0.0f, -25.0f,  0.0f, 1.0f, 0.0f,  2.0f, 2.0f
};

float cubeVertices[] = {
    // back face
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
     1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
    // front face
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
     1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
    // left face
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
    -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
    -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
    // right face
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
     1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
     1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
     // bottom face
     -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
     -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
     -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
     // top face
     -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
      1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
     -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
     -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
};


int main(void)
{
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    /* set opengl version */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Opengl Playground", NULL, NULL);
    if (!window)
    {
        std::cout << "Fail to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Fail to initialize glew" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    /* opengl config */
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClearColor(0.05f, 0.05f, 0.05f, 0.05f);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    /* init camera(position, center, up) */
    Camera camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    UserInput userInput(window, &camera);

    /* init shaders */
    Shader cubeShader("./res/simple.vs", "./res/simple.fs");
    Shader planeShader("./res/simple.vs", "./res/simple.fs");
    Shader lightShader("./res/light.vs", "./res/light.fs");
    Shader simplePhongShader("./res/simplePhong.vs", "./res/simplePhong.fs");

    /* cube setup */
    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    unsigned int cubeVBO;
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    /* plane setup */
    unsigned int planeVAO;
    glGenVertexArrays(1, &planeVAO);
    glBindVertexArray(planeVAO);

    unsigned int planeVBO;
    glGenBuffers(1, &planeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);


    /* light setup */
    glm::vec3 lightPosition(0.0f, 15.0f, 0.0f);
    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    unsigned int lightVBO;
    glGenBuffers(1, &lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    /* setup texture */
    Texture cubeTexture("./res/wood.png", 0);
    Texture planeTexture("./res/brick.png", 1);

    /* setup uniform */
    int numCube = 10;
    std::vector<glm::mat4> cubeModelMats;
    srand(glfwGetTime());

    for (int i = 0; i < numCube; i++)
    {
        glm::mat4 modelMat(1.0f);
        float x = rand() % 50 - 25;
        float y = rand() % 20;
        float z = rand() % 50 - 25;
        float rx = rand() % 100;
        float ry = rand() % 100;
        float rz = rand() % 100;
        float ang = rand() % 360;
        modelMat = glm::translate(modelMat, glm::vec3(x, y, z));
        modelMat = glm::rotate(modelMat, glm::radians(ang), glm::vec3(rx, ry, rx));
        modelMat = glm::scale(modelMat, glm::vec3(3.0f, 3.0f, 3.0f));
        cubeModelMats.push_back(modelMat);
    }

    cubeShader.bind();
    cubeShader.setUniform1i("tex", 0);
    cubeShader.unbind();

    planeShader.bind();
    planeShader.setUniform1i("tex", 1);
    planeShader.unbind();

    lightShader.bind();
    lightShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
    lightShader.unbind();

    simplePhongShader.bind();
    simplePhongShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
    simplePhongShader.unbind();

    float lightAngle = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        userInput.handleInput();
        userInput.handleMouse();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* draw call */

        // draw light
        lightShader.bind();
        glm::vec3 currLightPosition = lightPosition;
        glm::mat4 lightModelMats(1.0f);
        lightModelMats = glm::translate(lightModelMats, lightPosition);
        lightShader.setUniformMatrix4fv("model", glm::value_ptr(lightModelMats));
        lightShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        lightShader.unbind();



        // draw cube
        simplePhongShader.bind();
        glBindVertexArray(cubeVAO);
        for (int i = 0; i < numCube; i++)
        {
            simplePhongShader.setUniform1i("tex", 1);
            simplePhongShader.setUniform3fv("cameraPos", glm::value_ptr(camera.position));
            simplePhongShader.setUniform3fv("lightPos", glm::value_ptr(currLightPosition));
            simplePhongShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
            simplePhongShader.setUniformMatrix4fv("model", glm::value_ptr(cubeModelMats[i]));
            simplePhongShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);
        simplePhongShader.unbind();


        // draw cube
        simplePhongShader.bind();
        glBindVertexArray(cubeVAO);
        glm::mat4 centerModelMat(1.0f);

        simplePhongShader.setUniform1i("tex", 1);
        simplePhongShader.setUniform3fv("cameraPos", glm::value_ptr(camera.position));
        simplePhongShader.setUniform3fv("lightPos", glm::value_ptr(currLightPosition));
        simplePhongShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
        simplePhongShader.setUniformMatrix4fv("model", glm::value_ptr(centerModelMat));
        simplePhongShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        simplePhongShader.unbind();


        // draw plane
        glm::mat4 planeModelMat(1.0f);
        simplePhongShader.bind();
        simplePhongShader.setUniform1i("tex", 0);
        simplePhongShader.setUniform3fv("cameraPos", glm::value_ptr(camera.position));
        simplePhongShader.setUniform3fv("lightPos", glm::value_ptr(currLightPosition));
        simplePhongShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
        simplePhongShader.setUniformMatrix4fv("model", glm::value_ptr(planeModelMat));
        simplePhongShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        simplePhongShader.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}