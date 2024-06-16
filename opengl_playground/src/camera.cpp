#include "camera.h"
#include <string>
#include <iostream>
#include "glm/gtx/string_cast.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 ctr, glm::vec3 u)
	: position(pos), center(ctr), up(u)
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


void Camera::rotate(float yawAngle, float pitchAngle)
{
	yaw += yawAngle;
	pitch += pitchAngle;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	center = glm::normalize(front);

	glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));

}
