#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

#include "texture.h"

#include <iostream>


float vertices[] =
{
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	0.5f, 1.0f,
};

unsigned int indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4

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
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glew fail to load!" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    // init buffers & layouts
    VAO vao;
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    Shader shader("./res/vertexShader.shader", "./res/fragmentShader.shader");
    shader.bind();

    Texture texture("./res/brick.png", GL_TEXTURE0, 0);
    shader.setUniform1i("tex0", texture.unitID);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        /* draw call */
        glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}