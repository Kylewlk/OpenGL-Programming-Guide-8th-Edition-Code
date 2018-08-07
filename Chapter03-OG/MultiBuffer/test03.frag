#version 430 core

out vec4 fColor;

in vec4 oColor;

void main()
{
	fColor = oColor;
}

