#version 430 core
uniform mat4 matModel;
uniform mat4 matPorjectView;

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 vVertColor;

out vec4 color;

void main()
{
    gl_Position = matPorjectView * (matModel * pos);
    color = vVertColor;

}
