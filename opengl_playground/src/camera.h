#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <string>

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 center;
	glm::vec3 up;
	float speed;

	Camera(glm::vec3 p, glm::vec3 c, glm::vec3 u);

	glm::mat4 getMatrix();
	void move(const std::string& dir);
	void rotate(const std::string& dir);
};