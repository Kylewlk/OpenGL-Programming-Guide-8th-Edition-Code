#version 430

in vec2 texCoord;
uniform sampler2D depth_texture;

out vec4 color;

void main()
{
	color = texture(depth_texture, texCoord);
}