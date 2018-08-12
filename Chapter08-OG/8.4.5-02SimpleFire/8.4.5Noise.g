#version 410 core

out vec4 FragColor;

uniform float dt;

vec3 C1 = vec3(0.7, 0.0, 0.0);
vec3 C2 = vec3(0.88, 0.78, 0.0);
vec3 C3 = vec3(0.9, 0.9, 0.9);

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

float persistence = 1.0f / 1.40f;
int Number_Of_Octaves = 4;

float PerlinNoise_2D(vec2 x)
{

	float total = 0;
	float p = persistence;
	int n = Number_Of_Octaves;
	float frequency = 1.0f;
	float amplitude = 1.0f;
	for (int i = 1; i <= n; i++)
	{
		frequency *= 2.0;
		amplitude *= p;
		total = total + InterpolatedNoise_1(x * frequency) * amplitude;
	}
	
	return total;
}


void main()
{	
	if( fsPos.y < 0)
		discard;


	float f;
	
	Number_Of_Octaves = 3;
	
	Number_Of_Octaves = 6;	
	float n = abs(PerlinNoise_2D(vec2(fsTex.s, dt)))+ 0.1;//通过绝对值模拟火焰。

	if(fsPos.y > n)
		discard;

	float y = fsPos.y;
	float b1 = n * 0.4; //上面百分之40火焰透明

	float transparent = 1.0;
	if(n - y < b1)
	{
		transparent = (n-y)/b1;
	}

	float b2 = n * 1.0; //C1 红色区域
	float b3 = n * 0.6; //C2 黄色区域
	float b4 = n * 0.3; //C3 白色区域
	
	
	vec3 color = C1;
	if( y < b3 && y > b3 - 0.1 )
	{
		color = mix(C1, C2, (b3 - y) /0.1);
	}
	else if ( y < b3 -0.1 && y > b4)
	{
		color = C2;
	}
	else if(y <= b4 && y > b4 - 0.1)
	{
		color = mix(C2, C3, (b4 - y)/0.1);
	}
	else if(y <= b4 - 0.1)
	{
		color = C3;
	}
		
	FragColor = vec4(color, transparent); 
}






