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
    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.rotate("left");
    }
    if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.rotate("right");
    }
    if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        camera.rotate("up");
    }
    if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS)
    {
        camera.rotate("down");
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