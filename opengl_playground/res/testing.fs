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


float distLine(vec3 ro, vec3 rd, vec3 p)
{
	return length(cross(p-ro, rd)) / length(rd);
}
	


void main()
{
	vec2 uv = FragCoord;

	vec3 ro = vec3(0.0, 0.0, -2.0);
	vec3 rd = vec3(uv.x, uv.y, 0.0) - ro;

	float t = u_Time;
	mat3 rotationY = mat3(cos(t), 0.0, sin(t),
                0.0, 1.0, 0.0,
                -sin(t), 0.0, cos(t));
	mat3 rotationX = mat3(1.0, 0.0, 0.0,
                0.0, cos(t), -sin(t),
                0.0, sin(t), cos(t));
	vec3 p = rotationX * rotationY * vec3(2.0, 0.0, 0.0);
	p.z += 10.0;
	float d = distLine(ro, rd, p);
	d = smoothstep(0.1, 0.09, d);

	vec2 st = fract(uv*10);

	FragColor = vec4(st, 0.0, 1.0);	
}