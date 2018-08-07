#version 430 core

layout(location = 0) in vec4 pos;
layout(location = 1)  in vec4 col;


out vec4 oColor;

void main()
{
	gl_Position = pos;
	oColor = col;
}



