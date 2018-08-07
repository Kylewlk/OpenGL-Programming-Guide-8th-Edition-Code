#version 330 core

uniform vec3 LightPosition;


layout(location = 0) in vec4 MCVertex;
layout(location = 1) in vec2 TexCoord0;

flat out vec3 LightDir;
out vec3 EyeDir;
out vec2 TexCoord;
flat out vec3 EyeCoord;

//vec3 LightPosition = vec3(0.0f, 0.0f, -3.0f);
vec3 MCNormal = vec3(0.0, 0.0, -1.0);
vec3 MCTangent = vec3(0.0, 1.0, 0.0);

void main()
{
	EyeDir = vec3(MCVertex);
	TexCoord = TexCoord0.st;
	
	vec3 n = normalize(MCNormal);
	vec3 t = normalize(MCTangent);
	vec3 b = cross(n, t);
	
	vec3 v;
	v.x = dot(LightPosition, t);
	v.y = dot(LightPosition, b);
	v.z = dot(LightPosition, n);
	LightDir = normalize(v);

	v.x = dot(EyeDir, t);
	v.y = dot(EyeDir, b);
	v.z = dot(EyeDir, n);
	EyeDir = normalize(v);
	
	vec3 Eye = vec3(0.0, 0.0, -5.0);
	v.x = dot(Eye, t);
	v.y = dot(Eye, b);
	v.z = dot(Eye, n);
	EyeCoord = normalize(v);

	
	gl_Position = MCVertex;
}