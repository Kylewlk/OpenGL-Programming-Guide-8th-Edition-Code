#version 430

in vec2 texCoord;
uniform sampler2D depth_texture;

out vec4 color;

void main()
{

	color.rgb = texture(depth_texture, texCoord).r * vec3(1.0, 1.0, 1.0);//深度值存在R分量
	color.w=1.0;
}