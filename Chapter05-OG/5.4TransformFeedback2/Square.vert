#version 430 core

uniform vec4 vColor;
layout(location = 1) in vec4 vPos;

out vec4 color;

out vec4 oPostion;
out vec4 oPostion2;

void main()
{
	gl_Position = vPos;
	oPostion = vPos;
	color = vColor;
	oPostion2 = vec4(1.0);
}
