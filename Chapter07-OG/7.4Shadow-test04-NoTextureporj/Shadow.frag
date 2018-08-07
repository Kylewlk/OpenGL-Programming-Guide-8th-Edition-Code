#version 430 core

uniform sampler2D DepthTex;

uniform vec4 Ambient;

uniform vec3 LightColor;
uniform vec3 LightPosition;

uniform vec3 EyeDirection;
uniform float Attionuation;

in vec4 color;
in vec3 Normal;
in vec4 Pos;
in vec4 ShadowCoord;

out vec4 FragColor;

void main()
{
    vec3 lightDir = vec3(Pos.xyz) - LightPosition;
    float len = length(lightDir);
    lightDir = lightDir/len;
    vec3 HalfVector = normalize(EyeDirection - lightDir);
    
    
    float diffuse = max(0.0f, -1*dot(Normal, lightDir)) *0.5;
    float specular = max(0.0f, 1*dot(Normal, HalfVector));
    if(diffuse <= 0.00001)
        specular = 0.0f;

	vec3 shadow = ShadowCoord.xyz/ShadowCoord.w;//齐次空间坐标转换
	float d = texture(DepthTex, shadow.xy).r;//读取深度纹理中的深度值
	float f = 0.0;
	if(shadow.z <= d)//当前片元在Light视图下深度值小于等于深度纹理中的值，该片元没有被遮挡
	{
		f = 1.0;
	}
	
    vec4 scatteredLight = Ambient + vec4(LightColor * 0.5 * f, 0.0);
    vec4 ReflectLight = vec4(LightColor*specular * f, 0.0);

    FragColor = min(color*scatteredLight+ReflectLight, vec4(1.0));
}

