#include <iostream>

#include "userinput.h"
#include "camera.h"

UserInput::UserInput(GLFWwindow* window)
	: m_window(window)
{
}

void UserInput::handleInput(Camera& camera)
{
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.move("front");
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.move("left");
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.move("back");
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.move("right");
    }
    if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS)
    {
        camera.move("up");
    }
    if (glfwGetKey(m_window, GLFW_KEY_3) == GLFW_PRESS)
    {
        camera.move("down");
    }
}

void UserInput::handleMouse(GLFWwindow* window, Camera& camera)
{
    if (firstEnter)
    {
        double xIn, yIn;
        glfwGetCursorPos(window, &xIn, &yIn);

        xLast = static_cast<double>(xIn);
        yLast = static_cast<double>(yIn);
        firstEnter = false;
        return;
    }
    double xIn, yIn;
    glfwGetCursorPos(window, &xIn, &yIn);

    float xOffset = static_cast<double>(xIn) - xLast;
    float yOffset = yLast - static_cast<double>(yIn);

    float sensitivity = 0.1f;

    camera.rotate(xOffset * sensitivity, yOffset * sensitivity);
    
    xLast = static_cast<double>(xIn);
    yLast = static_cast<double>(yIn);
}