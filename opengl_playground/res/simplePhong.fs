#version 330 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex;
uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec3 cameraPos;


vec4 ambientTerm()
{
	float ambientStrength = 0.2;
	vec4 ambient = lightColor * ambientStrength * texture(tex, texCoord);
	return ambient;
}

vec4 diffuseTerm()
{
	float diffuseStrength = 1.0;
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - position);
	vec4 diffuse = lightColor * diffuseStrength * texture(tex, texCoord) * max(dot(norm, lightDir), 0.0);
	return diffuse;
}

vec4 specularTerm()
{
	float specularStrength = 0.5;
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - position);
	vec3 viewDir = normalize(cameraPos - position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	vec4 specular = lightColor * specularStrength * spec * texture(tex, texCoord);
	return specular;
}


void main()
{
	float distance = length(lightPos - position);
	float attenuation = 1.0 / (1.0 + 0.003 * (distance * distance));
	FragColor = attenuation * (ambientTerm() + diffuseTerm() + specularTerm());
}