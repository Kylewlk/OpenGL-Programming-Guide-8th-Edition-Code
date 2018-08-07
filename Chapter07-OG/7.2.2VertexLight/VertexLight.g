#version 430 core

uniform vec4 Ambient;

uniform vec3 LightColor;
uniform float Shininess;
uniform float Strength;

in vec4 color;
in vec3 Normal;
in vec4 Pos;

in vec3 LightDir;
in vec3 HalfVector;
in float Ationuat;

out vec4 FragColor;

void main()
{
    float diffuse = max(0.0f, -1*dot(Normal, LightDir)) *0.5;
    float specular = max(0.0f, 1*dot(Normal, HalfVector));
    if(diffuse <= 0.00001)
        specular = 0.0f;
    else
        specular = pow(specular, Shininess);

    vec4 scatteredLight = Ambient + vec4(LightColor * diffuse*Ationuat, 0.0);
    vec4 ReflectLight = vec4(LightColor*specular*Strength*Ationuat, 0.0);

    FragColor = min(color*scatteredLight+ReflectLight, vec4(1.0));
    
}