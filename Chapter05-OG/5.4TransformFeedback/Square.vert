#version 430 core

layout(location = 1) in vec4 vPos;

out vec4 oPostion;
out vec4 oPostion2;

void main()
{
	gl_Position = vPos;
	oPostion = vPos;
	oPostion2 = vec4(1.0);
}
