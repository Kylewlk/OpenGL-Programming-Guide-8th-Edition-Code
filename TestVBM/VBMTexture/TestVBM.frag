#version 410

uniform sampler2D tex;

layout (location = 0) out vec4 color;

in vec3 vs_fs_normal;
in vec2 fsTexCoord;

void main(void)
{
	vec4 texColor = texture(tex, fsTexCoord);

    color = vec4(0.1, 0.1, 0.1, 1.0) + vec4(0.7, 0.7, 0.7, 1.0) * abs(vs_fs_normal.z) + vec4(0.3, 0.3, 0.3, 1.0) * pow(abs(vs_fs_normal.z), 70.0);
	
	color = texColor * color;
	
}
