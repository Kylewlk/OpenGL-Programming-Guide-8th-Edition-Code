#version 430 core
uniform mat4 matModel;
uniform mat4 matPorjectView;
uniform mat4 matLightPorjectViewModle;

layout(location = 0) in vec4 vVertPos;
layout(location = 1) in vec4 vVertColor;
layout(location = 2) in vec3 vVertNormal;

out vec4 ShadowCoord;

void main()
{
    gl_Position = matPorjectView *  (matModel * vVertPos);
	ShadowCoord = matLightPorjectViewModle * vVertPos;
}