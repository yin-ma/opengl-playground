#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 600.0;

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), 
        vec2( 0.0f,    offset), 
        vec2( offset,  offset), 
        vec2(-offset,  0.0f),   
        vec2( 0.0f,    0.0f),   
        vec2( offset,  0.0f),   
        vec2(-offset, -offset), 
        vec2( 0.0f,   -offset), 
        vec2( offset, -offset)  
    );

    float kernel[9] = float[](
        1.0, 1.0, 1.0,
        1.0, -8.0, 1.0,
        1.0, 1.0, 1.0
    );

    vec4 col = vec4(0.0, 0.0, 0.0, 1.0);

    for (int i = 0; i < 9; i++)
    {
        col += texture(screenTexture, texCoords.st + offsets[i]) * kernel[i];
    }

    FragColor = col;
}