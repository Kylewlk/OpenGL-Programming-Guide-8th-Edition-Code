#version 410 core

out vec4 FragColor;

uniform float dt;

vec3 C1 = vec3(0.7, 0.0, 0.0);
vec3 C2 = vec3(0.88, 0.78, 0.0);
vec3 C3 = vec3(0.9, 0.9, 0.9);

in vec2 fsPos;
in vec2 fsTex;


float Noise1(int x)//����һ��[-1.0, 1.0]�����ڵ������
{
	x = (x << 13) ^ x;
	return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / (float(0x7fffffff)/2)/*1073741824.0*/);
}

float SmoothedNoise_1(int x) // ƽ���������ʹ�����������仯̫��
{
	return Noise1(x)* 4.0 / 10 + Noise1(x - 1) * 2.0 / 10 + Noise1(x + 1) * 2.0 / 10 + Noise1(x - 2) / 10 + Noise1(x + 2) / 10;
}

float InterpolatedNoise_1(float x)// �������ֵ�����Ǻ�����ֵ����ʹ�����������
{

	int integer_X = int(x);//��������
	float fractional_X = x - integer_X;//С������
	float v1 = SmoothedNoise_1(integer_X);
	float v2 = SmoothedNoise_1(integer_X + 1);

	float	ft = fractional_X * 3.141592f;
	float f = (1 + cos(ft)) * 0.5f;
	return v2*(1 - f) + v1*f;//��ֵ
}

float persistence = 1.0f / 1.20f;
int Number_Of_Octaves = 4;

float PerlinNoise_1D(float x) //����ͬƵ�ʵ���������
{
	float total = 0;
	float p = persistence;
	int n = Number_Of_Octaves;
	float frequency = 1.0f;
	float amplitude = 1.0f;
	for (int i = 1; i <= n; i++)
	{
		frequency *= 2.0;
		amplitude *= p; // Ƶ��Խ�ߵ��������ԽС
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
	float nt = abs(PerlinNoise_1D(fsTex.s + 200.0  + dt));
	float n = abs(PerlinNoise_1D(fsTex.s))+ 0.2;//ͨ������ֵģ����档

	n = (n + nt)/2.0;

	if(fsPos.y > n)
		discard;

	float y = fsPos.y;
	float b1 = n * 0.4; //����ٷ�֮40����͸��

	float transparent = 1.0;
	if(n - y < b1)
	{
		transparent = (n-y)/b1;
	}

	float b2 = n * 1.0; //C1 ��ɫ����
	float b3 = n * 0.6; //C2 ��ɫ����
	float b4 = n * 0.3; //C3 ��ɫ����
	
	
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






