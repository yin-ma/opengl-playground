#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 position;
out vec3 normal;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 cameraMat;

void main()
{
	position = vec3(model * vec4(aPos, 1.0));
	normal = vec3(model * vec4(aNormal, 0.0));
	texCoord = aTexCoord;
	gl_Position = cameraMat * model * vec4(aPos, 1.0);
}