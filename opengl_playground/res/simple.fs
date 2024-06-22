#version 330 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	FragColor = texture(tex, texCoord);
}