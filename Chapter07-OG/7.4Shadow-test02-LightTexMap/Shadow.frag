#version 430 core

uniform sampler2D ColorTex;


in vec4 ShadowCoord;

out vec4 FragColor;

void main()
{
	vec3 Shadow = ShadowCoord.xyz/ShadowCoord.w;//ShadowCoord为齐次空间坐标
	FragColor  = texture(ColorTex, Shadow.xy);
}

