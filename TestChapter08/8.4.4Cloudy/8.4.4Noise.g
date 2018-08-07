#version 410 core

out vec4 FragColor;

uniform float dt;

vec3 C1 = vec3(0.1, 0.1, 1.0);
vec3 C2 = vec3(1.0, 1.0, 1.0);

vec3 C3 = (C1+C2)/2.0;

in vec2 fsPos;
in vec2 fsTex;



float Noise1(ivec2 n)
{
	int x = n[0] +n[1]*57;
	x = (x << 13) ^ x;
	return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float SmoothedNoise_1(ivec2 x)
{
	return Noise1(x) / 2 + Noise1(x - 1) / 4 + Noise1(x + 1) / 4;
}

float Interpolate(float a, float b, float f)
{
	float ft = f * 3.1415926;
	float v = (1- cos(ft)) * 0.5f;
	return a*(1-v) + b*v;
}

float InterpolatedNoise_1(vec2 x)
{

	ivec2 integer_X = ivec2(x);
	vec2 fractional_X = x - integer_X;
	
	float v1 = SmoothedNoise_1(ivec2(integer_X));
	float v2 = SmoothedNoise_1(ivec2(integer_X[0]+1, integer_X[1]));
	float v3 = SmoothedNoise_1(ivec2(integer_X[0], integer_X[1]+1));
	float v4 = SmoothedNoise_1(ivec2(integer_X[0]+1, integer_X[1]+1));

	float i1 = Interpolate(v1, v2, fractional_X[0]);
	float i2 = Interpolate(v3, v4, fractional_X[0]);
	
	return Interpolate(i1, i2, fractional_X[1]);
}

float persistence = 1.0f / 1.30f;
int Number_Of_Octaves = 7;

float PerlinNoise_2D(vec2 x)
{

	float total = 0;
	float p = persistence;
	int n = Number_Of_Octaves;
	float frequency = 1.0f;
	float amplitude = 1.0f;
	for (int i = 1; i <= 2; i++)
	{
		frequency *= 2.0;
		amplitude *= p;
		total = total + InterpolatedNoise_1(x * frequency) * amplitude;
	}
	
	for (int i = 3; i <= n; i++)
	{
		frequency *= 2.0;
		amplitude *= p;
		total = total + InterpolatedNoise_1(x * frequency) * amplitude;
	}
	return total;
}


void main()
{
	vec2 Tex = fsTex;
	
	float f;
	
	
	
	f = clamp(PerlinNoise_2D(Tex+dt)+0.4125, 0.0, 1.0);
	

	// C1 = vec3(0.39, 0.37, 0.20);
	// C2 = vec3(0.5, 0.6, 0.3);
	// f = abs(PerlinNoise_2D(Tex)+0.212)*16 + fsPos.x*6.5;
	// f = sin(f)*0.5 +0.5;
	
	vec3 color = mix(C1, C2, f);
	
	
	// f = min(1.0, PerlinNoise_2D(Tex)*18.0);	
	// color= C1*f;
	
	FragColor = vec4(color, 1.0); 
}






