#pragma once

#include <string>
#include "GLFW/glfw3.h"
#include "camera.h"

class UserInput
{
public:
	UserInput(GLFWwindow* window);

	void handleInput(Camera& camera);
private:
	GLFWwindow* m_window;
};