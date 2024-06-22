#pragma once

#include <glm/glm.hpp>
#include <string>

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 center;
	glm::vec3 up;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float speed = 0.5f;
	float fov = 45.0f;
	float near = 0.1f;
	float far = 200.0f;
	float aspectRatio = 1.0f;

	Camera(glm::vec3 position, glm::vec3 center, glm::vec3 up);

	glm::mat4 getMatrix();
	void move(const std::string& direction);
	void rotate(float yawAngle, float pitchAngle);
	void zoom(float offset);
};