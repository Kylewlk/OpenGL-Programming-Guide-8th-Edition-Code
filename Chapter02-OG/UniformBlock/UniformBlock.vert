#version 430 core

//layout(binding = 1) uniform Named
//{
//	vec4 v[3];
//	vec4 color;
//} named;
//

layout(binding = 3) uniform Vertices
{
	vec4 v[3];
	vec4 color;
};

in uint n;

void main()
{
	gl_Position = v[n];
}