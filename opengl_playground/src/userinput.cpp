#include <GLFW/glfw3.h>

#include "userinput.h"
#include "camera.h"

#include <iostream>


UserInput::UserInput(GLFWwindow* m_window, Camera* m_camera)
    : m_window(m_window), m_camera(m_camera)
{
}

void UserInput::handleInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_camera->move("front");
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_camera->move("left");
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_camera->move("back");
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_camera->move("right");
    }
    if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS)
    {
        m_camera->move("up");
    }
    if (glfwGetKey(m_window, GLFW_KEY_3) == GLFW_PRESS)
    {
        m_camera->move("down");
    }
}

void UserInput::handleMouse()
{
    if (firstEnter)
    {
        double xIn, yIn;
        glfwGetCursorPos(m_window, &xIn, &yIn);

        xLast = static_cast<double>(xIn);
        yLast = static_cast<double>(yIn);
        firstEnter = false;
        return;
    }
    double xIn, yIn;
    glfwGetCursorPos(m_window, &xIn, &yIn);

    float xOffset = static_cast<double>(xIn) - xLast;
    float yOffset = yLast - static_cast<double>(yIn);

    float sensitivity = 0.1f;

    m_camera->rotate(xOffset * sensitivity, yOffset * sensitivity);
    
    xLast = static_cast<double>(xIn);
    yLast = static_cast<double>(yIn);
}