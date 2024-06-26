#version 330 core

in vec2 FragCoord;

out vec4 FragColor;

uniform float u_Time;

float circle(vec2 uv, vec2 p, float r, float blur)
{
	float d = length(uv - p);
	float c = smoothstep(r, r - blur, d);
	return c;
}

float band(float t, float start, float end, float blur)
{
	float step1 = smoothstep(start - blur, start + blur, t);
	float step2 = smoothstep(end + blur, end - blur, t);
	return step1 * step2;
}

float rect(vec2 uv, float top, float left, float width, float height, float blur)
{
	float band1 = band(uv.x, left, left+width, blur);
	float band2 = band(uv.y, top-height, top, blur);
	return band1 * band2;
}

float remap(float a, float b, float t)
{
	return clamp((t-a) / (b-a), 0.0, 1.0);
}

vec4 Head(vec2 uv)
{
	vec4 col = vec4(0.9, 0.65, 0.1, 1.0);

	float d = length(uv);
	col.a = smoothstep(0.5, 0.49, d);

	float edgeShadow = remap(0.35, 0.5, d);
	col.rgb *= 1 - edgeShadow * 0.5;

	return col;
}

vec4 Smiley(vec2 uv)
{
	vec4 col = vec4(0.0);
	vec4 head = Head(uv);

	col = mix(col, head, head.a);
	return col;
}

void main()
{
	vec2 uv = FragCoord;

	float d = length(uv);
	float t = u_Time;
	float col = circle(uv, vec2(sin(t), cos(t)), 0.3, 0.05);
	col += circle(uv, vec2(-0.2, 0.0), 0.1, 0.05);

	FragColor = vec4(vec3(col) *  vec3(0.7, 0.15, 0.15), 1.0);

	// FragColor = Smiley(uv);	
	// float d = length(uv);
	// FragColor = vec4(remap(0.35, 0.5, d), 0.0, 0.0, 1.0);
}