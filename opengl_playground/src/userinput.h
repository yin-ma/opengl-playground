#pragma once

#include <string>
#include "GLFW/glfw3.h"
#include "camera.h"

class UserInput
{
public:
	UserInput(GLFWwindow* window);

	void handleInput(Camera& camera);
	void handleMouse(GLFWwindow* window, Camera& camera);
private:
	GLFWwindow* m_window;
	float xLast = 300.0f;
	float yLast = 300.0f;
	bool firstEnter = true;
};