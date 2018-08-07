#version 430 core 

uniform vec4 Ambient;

uniform vec3 LightColor;
uniform vec3 LightDirection;

uniform vec3 HalfVector;
uniform float Shininess;
uniform float Strength;

in vec4 color;
in vec3 Normal;

out vec4 FragColor;

void main()
{
    float diffuse = max(0.0f, dot(Normal, -LightDirection));
    float specular = max(0.0f, dot(Normal, HalfVector));
    if(diffuse <= 0.00001)
        specular = 0.0f;
    else
        specular = pow(specular, Shininess);
    vec4 ReflectLight = vec4(LightColor*specular*Strength, 0.0);

    FragColor = min(color*Ambient+ReflectLight, vec4(1.0));

}
