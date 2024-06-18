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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        userInput.handleInput(camera);
        userInput.handleMouse(window, camera);

        /* draw call */
        defaultShader.bind();
        light.position = glm::rotate(light.position, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        defaultShader.setUniform3fv("lightPos", glm::value_ptr(light.position));
        model.draw(defaultShader, camera);
        light.draw(lightShader, camera);
        defaultShader.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}