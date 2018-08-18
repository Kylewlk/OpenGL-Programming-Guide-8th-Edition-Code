#version 430 core

layout(location=0) in vec4 Pos;
layout(location=1) in vec4 Color;

out vec4 fsColor;

void main()
{
	gl_Position = Pos;
	fsColor = Color;
}

