#version 430 core
uniform mat4 matModel;
uniform mat4 matPorjectView;

layout(location = 0) in vec4 vVertPos;
layout(location = 1) in vec4 vVertColor;
layout(location = 2) in vec3 vVertNormal;

out vec4 color;
out vec3 Normal;
out vec4 Pos;

void main()
{
    Pos = (matModel * vVertPos);
    gl_Position = matPorjectView * Pos;
    color = vVertColor;
    mat4 matNoral =  transpose(inverse(matModel));//������ת��������ԭ��ο��鱾592ҳ��¼E.1.2
    Normal = normalize((matNoral * vec4(vVertNormal, 0.0)).xyz);
}
