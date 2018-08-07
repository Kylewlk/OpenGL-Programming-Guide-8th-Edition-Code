#version 430 core

uniform mat4 modelMatrix;

layout(location=0) in vec4 VsPos;
layout(location=1) in vec3 VsNoraml;

out vec3 Normal;

void main()
{
	gl_Position = modelMatrix * VsPos;
	Normal = normalize((modelMatrix * vec4(VsNoraml, 0.0)).xyz);
}