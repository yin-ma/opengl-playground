#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

uniform mat4 cameraMat;
uniform mat4 model;

out vec3 position;
out vec3 color;
out vec2 texCoord;
out vec3 normal;

void main()
{
	position = vec3(model * vec4(aPos, 1.0));
	gl_Position = cameraMat * vec4(position, 1.0);
	color = aColor;
	texCoord = aTex;
	normal = aNormal;
};