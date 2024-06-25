#version 330 core

in vec2 FragCoord;

out vec4 FragColor;

void main()
{
	vec2 uv = FragCoord.xy;

	float d = length(uv);
	float c = d;
	float r = 0.3;
	c = smoothstep(0.3, 0.3-0.1, d);


	FragColor = vec4(vec3(c), 1.0);	
}