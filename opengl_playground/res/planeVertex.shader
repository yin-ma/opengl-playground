#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 position;
out vec3 normal;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
   gl_Position = cameraMatrix * model * vec4(aPos, 1.0f);
   position = aPos;
   normal = aNorm;
};