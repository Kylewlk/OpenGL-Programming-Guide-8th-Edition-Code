#version 410

layout (location = 0) in vec4 position;
layout (location = 1) in float fp;


out vec2 fsPos;
out float fsfp;

void main(void)
{
    gl_Position = position;
	fsPos = position.xy;
	fsfp = 2.0*(400.0/2.0)*position.x + 3.0*(400.0/2.0)*position.y + 200.0;
}
