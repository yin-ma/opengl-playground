#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;
layout (location = 4) mat4 model;

uniform mat4 cameraMat;

out vec3 position;
out vec3 color;
out vec2 texCoord;
out vec3 normal;

void main()
{
	gl_Position = cameraMat * model * vec4(aPos, 1.0);
	color = aColor;
	normal = aNormal;
	texCoord = aTex;
};