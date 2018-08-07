#version 410

uniform mat4 VMatrix;

layout (location = 0) in vec4 position;

out vec2 fsPos;


void main(void)
{
    gl_Position = VMatrix * position;
	fsPos = position.xy;
}
