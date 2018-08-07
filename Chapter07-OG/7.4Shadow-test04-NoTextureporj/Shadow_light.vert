#version 430 core
uniform mat4 matPorjectViewModle;

layout(location = 0) in vec4 vVertPos;
layout(location = 1) in vec4 vVertColor;

out vec4 color;

void main()
{
    gl_Position = matPorjectViewModle * vVertPos;
	color = vVertColor;
}
