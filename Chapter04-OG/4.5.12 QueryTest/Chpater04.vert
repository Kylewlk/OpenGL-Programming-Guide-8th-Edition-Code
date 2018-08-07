#version 430 core

layout(location = 0) in vec4 vColor;
layout(location = 1) in vec4 vPos;

/* sample  */out vec4 color;


void main()
{
	gl_Position = vPos;
	color = vColor;
}
