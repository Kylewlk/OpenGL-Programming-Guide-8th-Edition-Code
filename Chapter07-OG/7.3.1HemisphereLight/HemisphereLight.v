#version 430 core
uniform mat4 matModel;
uniform mat4 matPorjectView;

uniform vec3 LightSkyColor;
uniform vec3 LightGroundColor;
uniform vec3 LightPosition;


layout(location = 0) in vec4 vVertPos;
layout(location = 1) in vec4 vVertColor;
layout(location = 2) in vec3 vVertNormal;

out vec4 color;

void main()
{
    vec3 Pos = vec3(matModel * vVertPos);
    vec3 LightDir = normalize(Pos - LightPosition);
    mat4 matNoral =  transpose(inverse(matModel));
    vec3 Normal = normalize((matNoral * vec4(vVertNormal, 0.0)).xyz);
    float lightcos = dot(Normal, - LightDir)*0.5 + 0.5;
    vec3 LightColor = mix(LightGroundColor, LightSkyColor, lightcos);
    
    gl_Position = matPorjectView * matModel * vVertPos;
    color = vec4(vec3(vVertColor)*LightColor, vVertColor.a);
}
