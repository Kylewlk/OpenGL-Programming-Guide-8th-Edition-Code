#version 410
uniform sampler2D tex;

layout (location = 0) out vec4 color;


in vec3 gs_fs_normal;
in vec4 Color;

void main(void)
{
    color = Color*vec4(0.1, 0.1, 0.1, 1.0) + Color*vec4(0.4, 0.4, 0.4, 1.0) * abs(gs_fs_normal.z) + vec4(0.8, 0.8, 0.8, 1.0) * pow(abs(gs_fs_normal.z), 70.0);
}
