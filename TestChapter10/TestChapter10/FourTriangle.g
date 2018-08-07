#version 430 core

out vec4 fragColor;

flat in vec4 GsColor;

void main()
{
	fragColor = GsColor;
}



