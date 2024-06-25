#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"
#include "external/stb/stb_image.h"
#include <assimp/Importer.hpp>

#include "pointLight.cpp"

#include "vao.h"
#include "vbo.h"
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
     50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,  2.0f,  0.0f,
    -50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
    -50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,   0.0f, 2.0f,

     50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,  2.0f,  0.0f,
    -50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,   0.0f, 2.0f,
     50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,  2.0f, 2.0f
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* init camera(position, center, up) */
    Camera camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    UserInput userInput(window, &camera);

    /* init shaders */
    Shader lightShader("./res/light.vs", "./res/light.fs");
    Shader simpleDepthShader("./res/simpleDepth.vs", "./res/simpleDepth.fs");
    Shader shadowMappingShader("./res/shadowMapping.vs", "./res/shadowMapping.fs");

    /* cube setup */
    VAO cubeVAO;
    VBO cubeVBO(cubeVertices, sizeof(cubeVertices));
    cubeVAO.bind();
    cubeVBO.bind();
    cubeVBO.setLayoutf(0, 3, 8 * sizeof(float), 0);
    cubeVBO.setLayoutf(1, 3, 8 * sizeof(float), 3);
    cubeVBO.setLayoutf(2, 2, 8 * sizeof(float), 6);
    cubeVAO.unbind();


    /* plane setup */
    VAO planeVAO;
    VBO planeVBO(planeVertices, sizeof(planeVertices));
    planeVAO.bind();
    planeVBO.bind();
    planeVBO.setLayoutf(0, 3, 8 * sizeof(float), 0);
    planeVBO.setLayoutf(1, 3, 8 * sizeof(float), 3);
    planeVBO.setLayoutf(2, 2, 8 * sizeof(float), 6);
    planeVAO.unbind();

    /* light setup */
    glm::vec3 lightPosition(0.0f, 15.0f, 0.0f);
    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    float lightAngle = 0.0f;

    VAO lightVAO;
    VBO lightVBO(cubeVertices, sizeof(cubeVertices));
    lightVAO.bind();
    lightVBO.bind();
    lightVBO.setLayoutf(0, 3, 8 * sizeof(float), 0);
    lightVAO.unbind();

    /* setup texture */
    Texture cubeTexture("./res/wood.png", 0);
    Texture planeTexture("./res/brick.png", 1);

    /* setup uniform */
    glm::mat4 lightModelMat = glm::translate(glm::mat4(1.0f), lightPosition);

    lightShader.bind();
    lightShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
    lightShader.unbind();


    /* framebuffers */
    unsigned int SHADOW_WIDTH = 1024;
    unsigned int SHADOW_HEIGHT = 1024;

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    // create depth texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        userInput.handleInput();
        userInput.handleMouse();

        /* bind fbo */
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_BACK);

        // setup light
        glm::vec3 currLightPosition = lightPosition;
        glm::mat4 lightModelMats(1.0f);
        lightModelMats = glm::translate(lightModelMats, lightPosition);

        glm::mat4 lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.1f, 200.0f);
        glm::mat4 lightView = glm::lookAt(lightPosition, glm::vec3(0.0f, 5.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        /* draw call */
        simpleDepthShader.bind();
        simpleDepthShader.setUniformMatrix4fv("lightSpaceMatrix", glm::value_ptr(lightSpaceMatrix));

        // draw cube 1
        cubeVAO.bind();
        glm::mat4 cubeMat_1(1.0f);
        cubeMat_1 = glm::rotate(cubeMat_1, glm::radians(30.0f), glm::vec3(0.7, 0.3, 0.4));
        cubeMat_1 = glm::translate(cubeMat_1, glm::vec3(5.0f, 5.0f, -15.0f));
        simpleDepthShader.setUniformMatrix4fv("model", glm::value_ptr(cubeMat_1));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        cubeVAO.unbind();

        // draw cube 2
        cubeVAO.bind();
        glm::mat4 cubeMat_2(1.0f);
        cubeMat_2 = glm::translate(cubeMat_2, glm::vec3(0.0f, 5.0f, -20.0f));
        cubeMat_2 = glm::scale(cubeMat_2, glm::vec3(3.0f, 3.0f, 3.0f));
        simpleDepthShader.setUniformMatrix4fv("model", glm::value_ptr(cubeMat_2));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        cubeVAO.unbind();


        // draw plane
        glm::mat4 planeModelMat(1.0f);
        simpleDepthShader.setUniformMatrix4fv("model", glm::value_ptr(planeModelMat));
        planeVAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        planeVAO.unbind();
        simpleDepthShader.unbind();


        /* draw with depth buffer */
        glCullFace(GL_FRONT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE3);
        cubeTexture.bind();
        glActiveTexture(GL_TEXTURE4);
        planeTexture.bind();
        glActiveTexture(GL_TEXTURE11);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        // setup shadaow map shader
        shadowMappingShader.bind();
        shadowMappingShader.setUniformMatrix4fv("projection", glm::value_ptr(camera.getProjectionMat()));
        shadowMappingShader.setUniformMatrix4fv("view", glm::value_ptr(camera.getViewMat()));
        shadowMappingShader.setUniformMatrix4fv("lightSpaceMatrix", glm::value_ptr(lightSpaceMatrix));
        shadowMappingShader.setUniform3fv("viewPos", glm::value_ptr(camera.position));
        shadowMappingShader.setUniform3fv("lightPos", glm::value_ptr(currLightPosition));
        shadowMappingShader.setUniform1i("shadowMap", 11);

        // draw cube 1
        shadowMappingShader.bind();
        cubeVAO.bind();
        shadowMappingShader.setUniform1i("diffuseTexture", 4);
        shadowMappingShader.setUniformMatrix4fv("model", glm::value_ptr(cubeMat_1));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        cubeVAO.unbind();

        // draw cube 2
        cubeVAO.bind();
        shadowMappingShader.setUniform1i("diffuseTexture", 4);
        shadowMappingShader.setUniformMatrix4fv("model", glm::value_ptr(cubeMat_2));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        cubeVAO.unbind();



        // draw plane
        shadowMappingShader.setUniform1i("diffuseTexture", 3);
        shadowMappingShader.setUniformMatrix4fv("model", glm::value_ptr(planeModelMat));
        planeVAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        planeVAO.unbind();
        shadowMappingShader.unbind();

        // draw light
        lightShader.bind();
        lightShader.setUniformMatrix4fv("model", glm::value_ptr(lightModelMats));
        lightShader.setUniformMatrix4fv("view", glm::value_ptr(camera.getViewMat()));
        lightShader.setUniformMatrix4fv("projection", glm::value_ptr(camera.getProjectionMat()));
        lightVAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        lightVAO.unbind();
        lightShader.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}