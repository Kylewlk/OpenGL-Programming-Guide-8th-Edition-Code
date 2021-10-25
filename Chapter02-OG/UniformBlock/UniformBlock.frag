#version 430 core

layout(binding = 3) uniform Vertices
{
	vec4 v[3];
	vec4 color;
};

out vec4 Color;

void main()
{
	Color = color;
}