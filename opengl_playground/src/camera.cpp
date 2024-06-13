#include "camera.h"
#include <string>
#include <iostream>

Camera::Camera(glm::vec3 p, glm::vec3 c, glm::vec3 u)
	: position(p), center(c), up(u)
{
	speed = 0.1f;
}

glm::mat4 Camera::getMatrix()
{
	glm::mat4 view = glm::lookAt(position, position + center, up);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);

	return proj * view;
}

void Camera::move(const std::string& dir)
{
	if (dir == "up")
	{
		position += glm::normalize(up) * speed;
	}
	else if (dir == "down")
	{
		position -= glm::normalize(up) * speed;
	}
	else if (dir == "left")
	{
		position -= glm::normalize(glm::cross(center, up)) * speed;
	}
	else if (dir == "right")
	{
		position += glm::normalize(glm::cross(center, up)) * speed;
	}
	else if (dir == "front")
	{
		position += glm::normalize(center) * speed;
	}
	else if (dir == "back")
	{
		position -= glm::normalize(center) * speed;
	}
}


void Camera::rotate(const std::string& dir)
{
	if (dir == "left")
	{
		center = glm::rotate(center, glm::radians(1.0f), up);
	}
	else if (dir == "right")
	{
		center = glm::rotate(center, glm::radians(-1.0f), up);
	}
	else if (dir == "up")
	{
		center = glm::rotate(center, glm::radians(1.0f), glm::cross(center, up));
		up = glm::rotate(up, glm::radians(1.0f), glm::cross(center, up));
	}
	else if (dir == "down")
	{
		center = glm::rotate(center, glm::radians(-1.0f), glm::cross(center, up));
		up = glm::rotate(up, glm::radians(-1.0f), glm::cross(center, up));
	}
}
