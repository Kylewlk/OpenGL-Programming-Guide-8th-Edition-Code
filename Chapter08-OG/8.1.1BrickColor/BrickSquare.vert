#version 410

layout (location = 0) in vec4 position;

out vec2 fsPos;

void main(void)
{
    gl_Position = position;
	fsPos = position.xy;
}
