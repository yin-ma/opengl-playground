#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

Camera::Camera(glm::vec3 pos, glm::vec3 ctr, glm::vec3 u)
	: position(pos), center(ctr), up(u)
{
}
	
glm::mat4 Camera::getMatrix()
{
	glm::mat4 view = getViewMat();
	glm::mat4 proj = getProjectionMat();

	return proj * view;
}

glm::mat4 Camera::getProjectionMat()
{
	return glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

glm::mat4 Camera::getViewMat()
{
	return glm::lookAt(position, position + center, up);
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

void Camera::zoom(float offset)
{
	fov -= (float)offset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 89.0f)
		fov = 89.0f;
}
