#version 330 core

//; // 
float BumpDensity = 16.0;
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
	//vec2 c = BumpDensity * TexCoord.st;
	vec2 c = TexCoord.st;
	vec2 p = fract(c) - vec2(0.5);
	
	float d, f;
	d = dot(p,p);
	f = inversesqrt(d + 1.0);
	//float a = 0.8;
	if (d >= BumpSize) 
	{
		p = vec2(0.0);
		f = 1.0;
		//a= 1.0;
	}
	
	vec3 normDelta = vec3(p.x, p.y, 1.0) * f;
	//vec3 normDelta = vec3(-p.x, -p.y, 1.0) * f;
	litColor = SurfaceColor.rgb * max(dot(normDelta, LightDir), 0.0);
	vec3 reflectDir = reflect(-LightDir, normDelta);
	
	float spec = max(dot(normalize(EyeCoord - EyeDir), reflectDir), 0.0);
	//float spec = max(dot(EyeDir, reflectDir), 0.0);
	spec = pow(spec, 6.0);
	spec *= SpecularFactor;
	litColor = min(litColor + spec, vec3(1.0));
	//litColor = min(litColor + spec, vec3(1.0))*a;
	
	FragColor = vec4(litColor, SurfaceColor.a);
}