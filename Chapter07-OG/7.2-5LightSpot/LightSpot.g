#version 430 core

uniform vec4 Ambient;

uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 SoptDirection;
uniform float SoptCosCutoff;
uniform float SoptExponent;
uniform float Shininess;
uniform float Strength;

uniform vec3 EyeDirection;
uniform float Attionuation;

in vec4 color;
in vec3 Normal;
in vec4 Pos;

out vec4 FragColor;

void main()
{
    vec3 lightDir = vec3(Pos.xyz) - LightPosition;
    float len = length(lightDir);
    lightDir = normalize(lightDir);
    vec3 HalfVector = normalize(EyeDirection - lightDir);
    float Attenua = 1 / (Attionuation*(1.0+len*len));
    
    float diffuse = max(0.0f, -1*dot(Normal, lightDir)) *0.6;
    float specular = max(0.0f, 1*dot(Normal, HalfVector));
    if(diffuse <= 0.00001)
        specular = 0.0f;
    else
        specular = pow(specular, Shininess);

    float Spotcos = dot(SoptDirection, lightDir);
     
    if(Spotcos < SoptCosCutoff)
    {
        Attenua = 0.0f;
    }
    else
    {
        specular *= pow(Spotcos, SoptExponent);
        //specular *= ((Spotcos-1)/(1-SoptCosCutoff) + 1 )*2.0*Strength;
       
    }

    vec4 scatteredLight = Ambient + vec4(LightColor * diffuse*Attenua, 0.0); 
    vec4 ReflectLight = vec4(LightColor*specular*Attenua, 0.0);
    ;
    FragColor = min(color*scatteredLight + ReflectLight, vec4(1.0));

}
