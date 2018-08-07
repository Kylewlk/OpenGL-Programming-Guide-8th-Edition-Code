#version 410

uniform mat4 model_matrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 TexCoord;

out vec4 world_space_position;

out vec3 vs_fs_normal;
out vec2 fsTexCoord;


void main(void)
{
    vec4 pos = (model_matrix * (position * vec4(1.0, 1.0, 1.0, 1.0)));
    world_space_position = pos;
    vs_fs_normal = normalize((model_matrix * vec4(normal, 0.0)).xyz);
    gl_Position = pos;
	fsTexCoord = TexCoord;
}
