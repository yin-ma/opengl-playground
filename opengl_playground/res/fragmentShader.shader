#version 330 core
out vec4 FragColor;

in vec3 position;
in vec3 color;
in vec2 texCoord;
in vec3 normal;

uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec3 camPos;

void main()
{
	float ambient = 0.1f;

	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.25f;
	vec3 viewDirection = normalize(camPos - position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 12);
	float specular = specAmount * specularLight;

	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + specular + ambient);
}