#version 430 core

layout(location=0) in vec4 VsPos;

out vec2 texPos;

void main()
{
	gl_Position = VsPos;
	texPos = vec2(VsPos.xy)*0.5 + vec2(0.5, 0.5);
}