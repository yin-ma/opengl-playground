#pragma once

#include <string>
#include "GLFW/glfw3.h"
#include "camera.h"

class UserInput
{
public:
	Camera* m_camera;
	UserInput(GLFWwindow* window, Camera* camera);

	void handleInput();
	void handleMouse();
private:
	GLFWwindow* m_window;
	float xLast = 300.0f;
	float yLast = 300.0f;
	bool firstEnter = true;
};