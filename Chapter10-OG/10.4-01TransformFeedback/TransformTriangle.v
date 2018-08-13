#version 430 core

layout(location=0) in vec4 VSinPos;
layout(location=1) in vec4 VsinColor;

out vec4 VsGsColor;

void main()
{
	gl_Position = VSinPos;
	VsGsColor = VsinColor;
}