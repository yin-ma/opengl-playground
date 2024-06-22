#version 330 core

out vec4 FragColor;

in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;

uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec3 camPos;

void main()
{
	float ambient = 0.15f;

	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - position);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.55f;
	vec3 viewDirection = normalize(camPos - position);
	vec3 reflectionDirection = reflect(lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 18);
	float specular = specAmount * specularLight;

	vec4 diffuseTerm = lightColor * texture(texture_diffuse0, texCoord) * diffuse;
	vec4 ambientTerm = lightColor * texture(texture_diffuse0, texCoord) * ambient;
	vec4 speculaTerm = lightColor * texture(texture_specular0, texCoord) * specular;
	FragColor = ambientTerm + diffuseTerm + speculaTerm;
}