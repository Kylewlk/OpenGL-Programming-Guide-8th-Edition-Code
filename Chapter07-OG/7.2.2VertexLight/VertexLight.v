#version 430 core
uniform mat4 matModel;
uniform mat4 matPorjectView;

uniform vec3 LightPosition;
uniform vec3 EyeDirection;
uniform float Attionuation;


layout(location = 0) in vec4 vVertPos;
layout(location = 1) in vec4 vVertColor;
layout(location = 2) in vec3 vVertNormal;

out vec4 color;
out vec3 Normal;
out vec4 Pos;

out vec3 LightDir;
out vec3 HalfVector;
out float Ationuat;


void main()
{
    Pos = (matModel * vVertPos);
    LightDir = vec3(Pos.xyz) - LightPosition;
    float Len = length(LightDir);
    LightDir = LightDir/Len;

    HalfVector = EyeDirection - LightDir;

    Ationuat = 1/(1.0f+Attionuation*Len*Len);

    gl_Position = matPorjectView * Pos;
    color = vVertColor;
    mat4 matNoral =  transpose(inverse(matModel));
    Normal = normalize((matNoral * vec4(vVertNormal, 0.0)).xyz);
}

