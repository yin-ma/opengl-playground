#version 330 core

in vec3 position;
in vec3 normal;

out vec4 FragColor;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 lightColor;

void main()
{
	vec4 planeColor = vec4(0.42f, 0.12f, 0.12f, 1.0f);
	float ambient = 0.2f;

	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(cameraPosition - position);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 1000);
	float specular = specAmount * specularLight;

	FragColor = lightColor * planeColor * (diffuse + ambient + specular);
};