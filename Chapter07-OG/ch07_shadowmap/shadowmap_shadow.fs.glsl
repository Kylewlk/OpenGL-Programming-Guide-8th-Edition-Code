#version 430 core

layout (location = 0) out vec4 color;

uniform vec3 material_ambient;

void main(void)
{
    color = vec4(material_ambient*3.0f, 1.0);
}
