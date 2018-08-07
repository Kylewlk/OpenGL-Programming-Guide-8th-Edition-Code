#version 430 core

layout(location = 0) in vec4 vColor;
layout(location = 1) in vec4 vPos;

out vec4 color;

float gl_ClipDistance[1];

void main()
{
	gl_Position = vPos;
	color = vColor;
    gl_ClipDistance[0] = 0.2 - vPos.y;
}
