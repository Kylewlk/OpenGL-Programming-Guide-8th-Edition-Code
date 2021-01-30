#version 430 core

uniform mat4 VMatrix;

layout(location = 0) in vec4 vertex;

out vec4 position;
out vec4 Vpos;

void main()
{
	position = vertex;
	Vpos = VMatrix * vertex;
	gl_Position = Vpos;
	
}




