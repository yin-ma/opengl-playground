#include "camera.h"

Camera::Camera(glm::vec3 p, glm::vec3 c, glm::vec3 u)
	: position(p), center(c), up(u)
{

}

glm::mat4 Camera::getMatrix()
{
	glm::mat4 view = glm::lookAt(position, position + center, up);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

	return proj * view;
}