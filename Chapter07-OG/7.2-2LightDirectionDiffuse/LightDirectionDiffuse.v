#version 430 core 
uniform mat4 matModel;
uniform mat4 matPorjectView;

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 vVertColor;
layout(location = 2) in vec3 vVertNormal;

out vec4 color;
out vec3 Normal;

void main()
{
    gl_Position = matPorjectView * (matModel * pos);
    color = vVertColor;
    mat3 matNoral =  transpose(inverse(mat3(matModel)));//������ת��������ԭ��ο��鱾592ҳ��¼E.1.2
    Normal = normalize(matNoral * vVertNormal);

}
