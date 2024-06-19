#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "vertex.h"
#include "userinput.h"

#include "pointLight.cpp"

#include <vector>
#include <iostream>
#include <string>


const int SCR_WIDTH = 600;
const int SCR_HEIGHT = 600;

float rectangleVertices[] =
{
    // Coords    // texCoords
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,

     1.0f,  1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f
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


    /* init camera(position, center, up) */
    Camera camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    UserInput userInput(window);

    /* init shaders */
    Shader defaultShader("./res/default.vs", "./res/default.fs");
    Shader lightShader("./res/light.vs", "./res/light.fs");

    /* load model */
    Model model("./res/model/nanosuit.obj");
    PointLight light(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    lightShader.bind();
    lightShader.setUniform4fv("lightColor", glm::value_ptr(light.color));
    lightShader.unbind();

    defaultShader.bind();
    defaultShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
    defaultShader.setUniformMatrix4fv("model", glm::value_ptr(glm::mat4(1.0f)));
    defaultShader.setUniform3fv("lightPos", glm::value_ptr(light.position));
    defaultShader.setUniform4fv("lightColor", glm::value_ptr(light.color));
    defaultShader.unbind();


    /* framebuffer */
    Shader framebufferProgram("./res/framebuffer.vs", "./res/framebuffer.fs");
    Shader orgFramebufferProgram("./res/orgFramebuffer.vs", "./res/orgFramebuffer.fs");
    
    unsigned int rectVAO, rectVBO;
    glGenVertexArrays(1, &rectVAO);
    glGenBuffers(1, &rectVBO);
    glBindVertexArray(rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    unsigned int FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 600, 600);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    // Create Framebuffer Texture
    unsigned int framebufferTexture;
    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    glEnable(GL_DEPTH_TEST);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        userInput.handleInput(camera);
        userInput.handleMouse(window, camera);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        /* draw call */
        defaultShader.bind();
        light.position = glm::rotate(light.position, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        defaultShader.setUniform3fv("lightPos", glm::value_ptr(light.position));
        model.draw(defaultShader, camera);
        light.draw(lightShader, camera);
        defaultShader.unbind();

        // Draw the framebuffer fisrt half rect
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        framebufferProgram.bind();
        framebufferProgram.setUniform1i("screenTexture", 1);
        glBindVertexArray(rectVAO);
        glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
        glBindTexture(GL_TEXTURE_2D, framebufferTexture);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        framebufferProgram.unbind();

        // Draw the framebuffer second half rect
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        orgFramebufferProgram.bind();
        orgFramebufferProgram.setUniform1i("screenTexture", 1);
        glBindVertexArray(rectVAO);
        glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
        glBindTexture(GL_TEXTURE_2D, framebufferTexture);
        glDrawArrays(GL_TRIANGLES, 3, 6);
        glBindVertexArray(0);
        orgFramebufferProgram.unbind();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}