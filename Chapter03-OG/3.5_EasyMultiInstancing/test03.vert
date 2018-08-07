#version 430 core

layout(location = 0) in vec4 pos;
layout(location = 1)  in vec4 col;

layout(location = 2) in vec4 PosOffset;//每个实例更新一次

out vec4 oColor;

void main()
{
	gl_Position =  pos + PosOffset;
	oColor = col;
}



