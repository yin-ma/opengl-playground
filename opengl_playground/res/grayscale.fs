#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

void main()
{
    vec4 tex = texture(screenTexture, texCoords);
    float averge = 0.2126 * tex.r + 0.7152 * tex.g + 0.0722 * tex.b;
    FragColor = vec4(averge, averge, averge, 1.0);
}