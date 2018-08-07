#version 430 core

uniform vec4 Ambient;

uniform vec3 LightColor;
uniform vec3 LightDirection;

in vec4 color;
in vec3 Normal;

out vec4 FragColor;

void main()
{
    float diffuse = max(0.0f, dot(Normal, -LightDirection));
    vec4 scatteredLight = Ambient + vec4(LightColor*diffuse, 0.0);
    FragColor = min(color*scatteredLight, vec4(1.0));

}
