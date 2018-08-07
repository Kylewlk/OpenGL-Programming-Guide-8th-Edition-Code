#version 430 core

in vec2 TexCoord;

layout(location = 0) uniform sampler2D tex;

out vec4 fColor;

void main()
{
	fColor = texture(tex, gl_PointCoord);
}

