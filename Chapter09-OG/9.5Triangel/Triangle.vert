#version 430 core

layout(location = 0) in vec4 VsInPos;
layout(location = 1) in vec4 VsInColor;

out vec4 color;

void main()
{
	gl_Position = VsInPos;
	color = VsInColor;
}


