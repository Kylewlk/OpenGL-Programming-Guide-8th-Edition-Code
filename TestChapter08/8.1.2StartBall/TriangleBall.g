#version 430 core

const int PanelCount = 3;
uniform vec4 Panel[PanelCount];

uniform vec4 BaseColor;
uniform vec4 PatternColor;

const float FWidth = 0.005;
const vec4 LightColor = vec4(0.8, 0.8,0.8, 1.0);
const vec4 ambient = vec4(0.1, 0.2, 0.1, 1.0);
const vec4 diffuse = vec4(0.4, 0.3, 0.5, 1.0);
const vec3 LightDir = normalize(vec3(-1.0, -1.0, 1.0));
const vec3 EyeDir = vec3(0.0, 0.0, 1.0);

in vec4 position;
in vec4 Vpos;

out vec4 FragColor;

void main()
{
	vec4 sPos;
	sPos.xyz =  normalize(position.xyz);
	sPos.w = 1.0;
	
	float d = 0.0, t= 0.0;
	for(int i = 0; i < PanelCount; ++i)
	{
		t = dot(Panel[i], sPos);
		d += smoothstep(-FWidth, FWidth, t);
	}
	d -=2.0;
	d = clamp(d, 0.0, 1.0) ;
	//d = d/3.0;
	
	vec4 color = mix(BaseColor, PatternColor, d);
	
	vec3 normal = normalize(Vpos.xyz);
	vec3 Reflect = reflect(LightDir, normal);
	float diff, specular;
	diff = clamp(dot(-LightDir, normal), 0.0, 1.0);
	specular = clamp(dot(Reflect, -EyeDir), 0.0, 1.0);
	specular = pow(specular, 50);

	FragColor = color * ambient + color*LightColor*diff + LightColor* 0.7 * specular;
	FragColor = min(FragColor, vec4(1.0));
	//FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}

