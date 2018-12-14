#version 410
uniform sampler2D tex;

layout (location = 0) out vec4 color;


in vec3 vs_fs_normal;
in vec2 vs_fs_tex;

void main(void)
{
	vec4 texColor = texture(tex,vec2(vs_fs_tex.x, vs_fs_tex.y));
	//vec4 texColor = vec4(1.0, 0.0, 0.0, 1.0) * vs_fs_tex.x + vec4(0.0, 1.0, 0.0, 1.0)* vs_fs_tex.y;

    color = texColor*vec4(0.1, 0.1, 0.1, 1.0) + texColor*vec4(0.4, 0.4, 0.4, 1.0) * abs(vs_fs_normal.z) + texColor*vec4(0.8, 0.8, 0.8, 1.0) * pow(abs(vs_fs_normal.z), 70.0);
}
