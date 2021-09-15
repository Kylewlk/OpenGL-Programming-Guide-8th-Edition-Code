#version 430 core

layout(binding = 3) uniform Vertice
{
	vec4 v[3];
	vec4 color;
};

in uint n;

void main()
{
	gl_Position = v[n];
}