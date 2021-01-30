#version 330 core

//; // 
float BumpDensity = 6.0;
float BumpSize = 0.15;
vec4 SurfaceColor = vec4(0.7, 0.6, 0.18, 1.0);
float SpecularFactor = 0.5;

flat in vec3 LightDir;
in vec3 EyeDir;
in vec2 TexCoord;
flat in vec3 EyeCoord;

out vec4 FragColor;

void main()
{
	vec3 litColor;
	vec2 c = BumpDensity * TexCoord.st;
	//vec2 c = TexCoord.st;
	vec2 p = fract(c) - vec2(0.5);//p代表与圆心的相对位置
	
	float d, f;
	d = dot(p,p);
	
	// f = inversesqrt(d + 1.0);
	// if (d >= BumpSize) 
	// {
		// p = vec2(0.0);
		// f = 1.0;
	// }	
	// vec3 normDelta = vec3(p.x, p.y, 1.0) * f;

	vec3 normDelta = normalize(vec3(p.x, p.y, 1.0));
	if (d >= BumpSize) 
	{		
		normDelta = vec3(0.0, 0.0, 1.0);
	}	
	else
	{
		normDelta = normalize(vec3(p.x, p.y, 1.0));//法线偏移，使得看上去凸起
	}	

	litColor = SurfaceColor.rgb * max(dot(normDelta, LightDir), 0.0);
	vec3 reflectDir = reflect(-LightDir, normDelta);
	
	float spec = max(dot(normalize(EyeCoord - EyeDir), reflectDir), 0.0);
	//float spec = max(dot(EyeDir, reflectDir), 0.0);
	spec = pow(spec, 16.0);
	spec *= SpecularFactor;
	litColor = min(litColor + spec, vec3(1.0));
	
	FragColor = vec4(litColor, SurfaceColor.a);
}