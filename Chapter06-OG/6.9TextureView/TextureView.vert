#version 430 core

layout(location = 0) in vec4 vPos;
layout(location = 1) in vec2 vTexCoord;

layout(location = 1) uniform mat4 ModelView;

out vec2 TexCoord;

void main()
{
	gl_Position = ModelView * vPos;
	TexCoord = vTexCoord;
}
