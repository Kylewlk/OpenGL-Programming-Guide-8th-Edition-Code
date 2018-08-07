#version 430 core

out vec4 fragColor;

in vec4 VsGsColor;

void main()
{
	fragColor = VsGsColor;
}



