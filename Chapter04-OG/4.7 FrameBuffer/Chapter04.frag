#version 430 core

/* sample  */in vec4 color;

layout(location = 0) out vec4 fColor;//输出到GL_COLOR_ATTACHMENT0
layout(location = 1) out vec4 fColor2;//输出到GL_COLOR_ATTACHMENT1

void main()
{
	fColor = color;
	fColor2 = vec4(0.0, 0.0, 1.0, 1.0);
}

