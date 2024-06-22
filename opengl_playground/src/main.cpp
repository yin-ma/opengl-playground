#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

#include "pointLight.cpp"

#include "vao.h"
#include "vbo.h"
#include "camera.h"
#include "shader.h"
#include "model.h"
#include "vertex.h"
#include "userinput.h"

#include <vector>
#include <iostream>
#include <string>


const int SCR_WIDTH = 600;
const int SCR_HEIGHT = 600;

float cubeVertices[] = {
    // back face
    -1.0f, -1.0f, -1.0f,  // bottom-left
     1.0f,  1.0f, -1.0f,  // top-right
     1.0f, -1.0f, -1.0f,  // bottom-right         
     1.0f,  1.0f, -1.0f,  // top-right
    -1.0f, -1.0f, -1.0f,  // bottom-left
    -1.0f,  1.0f, -1.0f,  // top-left
    // front face         
    -1.0f, -1.0f,  1.0f,  // bottom-left
     1.0f, -1.0f,  1.0f,  // bottom-right
     1.0f,  1.0f,  1.0f,  // top-right
     1.0f,  1.0f,  1.0f,  // top-right
    -1.0f,  1.0f,  1.0f,  // top-left
    -1.0f, -1.0f,  1.0f,  // bottom-left
    // left face          
    -1.0f,  1.0f,  1.0f,  // top-right
    -1.0f,  1.0f, -1.0f,  // top-left
    -1.0f, -1.0f, -1.0f,  // bottom-left
    -1.0f, -1.0f, -1.0f,  // bottom-left
    -1.0f, -1.0f,  1.0f,  // bottom-right
    -1.0f,  1.0f,  1.0f,  // top-right
    // right face         
     1.0f,  1.0f,  1.0f,  // top-left
     1.0f, -1.0f, -1.0f,  // bottom-right
     1.0f,  1.0f, -1.0f,  // top-right         
     1.0f, -1.0f, -1.0f,  // bottom-right
     1.0f,  1.0f,  1.0f,  // top-left
     1.0f, -1.0f,  1.0f,  // bottom-left     
     // bottom face       
     -1.0f, -1.0f, -1.0f,  // top-right
      1.0f, -1.0f, -1.0f,  // top-left
      1.0f, -1.0f,  1.0f,  // bottom-left
      1.0f, -1.0f,  1.0f,  // bottom-left
     -1.0f, -1.0f,  1.0f,  // bottom-right
     -1.0f, -1.0f, -1.0f,  // top-right
     // top face          
     -1.0f,  1.0f, -1.0f,  // top-left
      1.0f,  1.0f , 1.0f,  // bottom-right
      1.0f,  1.0f, -1.0f,  // top-right     
      1.0f,  1.0f,  1.0f,  // bottom-right
     -1.0f,  1.0f, -1.0f,  // top-left
     -1.0f,  1.0f,  1.0f,  // bottom-left        
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
    Shader defaultShader("./res/default.vs", "./res/default.fs");
    Shader lightShader("./res/light.vs", "./res/light.fs");

    /* load model */
    Model planet("./res/planet/planet.obj");
    Model rock("./res/rock/rock.obj");

    /* setup light(position, color) */
    glm::vec3 lightPosition = glm::vec3(0.0f, 20.0f, 20.0f);
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    VAO lightVAO;
    VBO lightVBO(cubeVertices, sizeof(cubeVertices));
    lightVAO.bind();
    lightVBO.bind();
    lightVBO.setLayoutf(0, 3, 3 * sizeof(float), 0);
    lightVAO.unbind();

    defaultShader.bind();
    defaultShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
    defaultShader.setUniformMatrix4fv("model", glm::value_ptr(glm::mat4(1.0f)));
    defaultShader.setUniform3fv("lightPos", glm::value_ptr(lightPosition));
    defaultShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
    defaultShader.unbind();

    glEnable(GL_DEPTH_TEST);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        userInput.handleInput();
        userInput.handleMouse();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* draw call */
        lightShader.bind();
        lightVAO.bind();
        lightShader.setUniformMatrix4fv("cameraMat", glm::value_ptr(camera.getMatrix()));
        lightShader.setUniformMatrix4fv("model", glm::value_ptr(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f)), lightPosition)));
        lightShader.setUniform4fv("lightColor", glm::value_ptr(lightColor));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        lightShader.unbind();
        lightVAO.unbind();

        planet.draw(defaultShader, camera);
        rock.draw(defaultShader, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}